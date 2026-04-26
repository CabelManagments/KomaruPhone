#ifndef KOMARU_CRYPTO_H
#define KOMARU_CRYPTO_H

#include <stdint.h>

void komaru_crypto_aes256_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output, int len);
void komaru_crypto_aes256_decrypt(const uint8_t *key, const uint8_t *input, uint8_t *output, int len);
void komaru_crypto_sha256(const uint8_t *input, int len, uint8_t *output);
void komaru_crypto_random_bytes(uint8_t *buf, int len);

#endif
