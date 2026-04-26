#include "komaru_crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Простая XOR-заглушка (для реального шифрования нужна libssl)
void komaru_crypto_aes256_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output, int len) {
    (void)key;
    for(int i = 0; i < len; i++) output[i] = input[i] ^ 0xAA;
}

void komaru_crypto_aes256_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output, int len) {
    (void)key;
    for(int i = 0; i < len; i++) output[i] = input[i] ^ 0xAA;
}

void komaru_crypto_sha256(const uint8_t *input, int len, uint8_t *output) {
    (void)input;
    (void)len;
    memset(output, 0, 32);
}

void komaru_crypto_random_bytes(uint8_t *buf, int len) {
    srand(time(NULL));
    for(int i = 0; i < len; i++) buf[i] = rand() % 256;
}
