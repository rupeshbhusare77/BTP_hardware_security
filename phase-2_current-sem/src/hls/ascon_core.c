#include "api.h"
#include "permutations.h"

#define RATE (64 / 8)
#define PA_ROUNDS 12
#define PB_ROUNDS 6
#define IV                                                        \
  ((u64)(8 * (CRYPTO_KEYBYTES)) << 56 | (u64)(8 * (RATE)) << 48 | \
   (u64)(PA_ROUNDS) << 40 | (u64)(PB_ROUNDS) << 32)

int ascon_core(unsigned char* d_out, unsigned long long* d_out_len,
               const unsigned char* d_in, unsigned long long d_in_len,
               const unsigned char* ad, unsigned long long adlen,
               const unsigned char* nsec, const unsigned char* npub,
               const unsigned char* k, int mode) {

  // --- HARDWARE INTERFACE PRAGMAS ---
  // This tells the Verilog testbench to allocate enough memory to hold our data!
  #pragma HLS INTERFACE ap_memory port=d_in depth=100
  #pragma HLS INTERFACE ap_memory port=d_out depth=100
  #pragma HLS INTERFACE ap_memory port=ad depth=100
  #pragma HLS INTERFACE ap_memory port=npub depth=16
  #pragma HLS INTERFACE ap_memory port=k depth=16

  // Load Key and Nonce (Untouched from your template)
  const u64 K0 = BYTES_TO_U64(k, 8);
  const u64 K1 = BYTES_TO_U64(k + 8, 8);
  const u64 N0 = BYTES_TO_U64(npub, 8);
  const u64 N1 = BYTES_TO_U64(npub + 8, 8);
  state s;
  (void)nsec;

  // --- STAGE 1: Length Calculation based on Mode ---
  unsigned long long data_len;
  if (mode == 0) { // Encrypt
    data_len = d_in_len;
    *d_out_len = d_in_len + CRYPTO_ABYTES; 
  } else {         // Decrypt
    if (d_in_len < CRYPTO_ABYTES) {
      *d_out_len = 0;
      return -1; // Invalid ciphertext length
    }
    data_len = d_in_len - CRYPTO_ABYTES;
    *d_out_len = data_len;
  }

  // --- STAGE 2: Shared Initialization ---
  s.x0 = IV;
  s.x1 = K0;
  s.x2 = K1;
  s.x3 = N0;
  s.x4 = N1;
  printstate("initial value:", s);
  P12(&s);
  s.x3 ^= K0;
  s.x4 ^= K1;
  printstate("initialization:", s);

  // --- STAGE 3: Shared Associated Data (AD) ---
  if (adlen) {
    while (adlen >= RATE) {
      s.x0 ^= BYTES_TO_U64(ad, 8);
      P6(&s);
      adlen -= RATE;
      ad += RATE;
    }
    s.x0 ^= BYTES_TO_U64(ad, adlen);
    s.x0 ^= 0x80ull << (56 - 8 * adlen);
    P6(&s);
  }
  s.x4 ^= 1; // Domain separation (Standard Ascon rule)

  // --- STAGE 4: Data Processing (The Split Logic) ---
  while (data_len >= RATE) {
    if (mode == 0) { // Encrypt: state ^ plaintext = ciphertext
      s.x0 ^= BYTES_TO_U64(d_in, 8);
      U64_TO_BYTES(d_out, s.x0, 8);
    } else {         // Decrypt: state ^ ciphertext = plaintext
      u64 ci = BYTES_TO_U64(d_in, 8);
      U64_TO_BYTES(d_out, s.x0 ^ ci, 8);
      s.x0 = ci;     // State absorbs ciphertext
    }
    P6(&s);
    data_len -= RATE;
    d_in += RATE;
    d_out += RATE;
  }

  // Final fractional block handling
  if (mode == 0) { // Encrypt
    s.x0 ^= BYTES_TO_U64(d_in, data_len);
    s.x0 ^= 0x80ull << (56 - 8 * data_len);
    U64_TO_BYTES(d_out, s.x0, data_len);
  } else {         // Decrypt
    u64 ci = BYTES_TO_U64(d_in, data_len);
    u64 pi = s.x0 ^ ci;
    U64_TO_BYTES(d_out, pi, data_len);
    // Cleanly replace only the valid bytes in the state with ciphertext bytes
    s.x0 ^= BYTES_TO_U64(d_out, data_len); 
    s.x0 ^= 0x80ull << (56 - 8 * data_len);
  }
  d_in += data_len;
  d_out += data_len;

  // --- STAGE 5: Shared Finalization ---
  s.x1 ^= K0;
  s.x2 ^= K1;
  P12(&s);
  s.x3 ^= K0;
  s.x4 ^= K1;

  // --- STAGE 6: Tag Generation / Verification ---
  if (mode == 0) { // Encrypt: Output the Tag
    U64_TO_BYTES(d_out, s.x3, 8);
    U64_TO_BYTES(d_out + 8, s.x4, 8);
    return 0; // Success
  } else {         // Decrypt: Verify the Tag
    unsigned char expected_tag[16];
    U64_TO_BYTES(expected_tag, s.x3, 8);
    U64_TO_BYTES(expected_tag + 8, s.x4, 8);
    
    int result = 0;
    // Note: d_in pointer naturally moved forward to point exactly at the received tag!
    for (int i = 0; i < 16; i++) {
      result |= d_in[i] ^ expected_tag[i];
    }
    
    if (result != 0) {
      *d_out_len = 0; // Wipe output length on failure
      return -1;      // Tamper detected!
    }
    return 0; // Success
  }
}