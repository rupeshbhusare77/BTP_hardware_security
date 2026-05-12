#ifndef API_H
#define API_H

#define CRYPTO_KEYBYTES 16
#define CRYPTO_NSECBYTES 0
#define CRYPTO_NPUBBYTES 16
#define CRYPTO_ABYTES 16
#define CRYPTO_NOOVERLAP 1

// Unified Hardware Top Function
// mode: 0 = Encrypt, 1 = Decrypt
int ascon_core(unsigned char* d_out, unsigned long long* d_out_len,
               const unsigned char* d_in, unsigned long long d_in_len,
               const unsigned char* ad, unsigned long long adlen,
               const unsigned char* nsec, const unsigned char* npub,
               const unsigned char* k, int mode);

#endif