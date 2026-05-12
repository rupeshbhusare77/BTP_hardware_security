#include <stdio.h>
#include <string.h>
#include "api.h"

int main() {
    // 1. Setup our dummy data
    unsigned char key[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    unsigned char nonce[16] = {0}; // All zeros for simplicity
    unsigned char ad[8] = "BTP_DATA"; // Associated Data
    unsigned char plaintext[14] = "Hello Allmight"; // 14 bytes
    
    unsigned char ciphertext[100] = {0};
    unsigned char decrypted_text[100] = {0};
    unsigned long long c_len, d_len;

    printf("--- STARTING ASCON TESTBENCH ---\n");
    printf("Original Message: %s\n\n", plaintext);

    // 2. Test Encryption (mode = 0)
    int enc_status = ascon_core(ciphertext, &c_len, plaintext, 14, ad, 8, NULL, nonce, key, 0);
    if (enc_status == 0) {
        printf("Encryption SUCCESS! Ciphertext length: %llu bytes\n", c_len);
    }

    // 3. Test Decryption (mode = 1)
    // We feed the generated 'ciphertext' back into 'd_in'
    int dec_status = ascon_core(decrypted_text, &d_len, ciphertext, c_len, ad, 8, NULL, nonce, key, 1);
    if (dec_status == 0) {
        printf("Decryption SUCCESS! Recovered length: %llu bytes\n", d_len);
        printf("Recovered Message: %s\n", decrypted_text);
    } else {
        printf("Decryption FAILED! Tag mismatch.\n");
    }

// 4. Final Verification (Hardware Style)
    // We use memcmp to compare EXACTLY 14 bytes, ignoring strings!
    if (memcmp(plaintext, decrypted_text, 14) == 0) {
        printf("\nRESULT: PASS! The core works perfectly.\n");
        return 0;   //this will tell hls simulation is passed.
    } else {
        printf("\nRESULT: FAIL! Outputs do not match.\n");
        return 1;   //this will tell hls simulation is failed.
    }
}