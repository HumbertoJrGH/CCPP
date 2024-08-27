#ifndef CIPHER_H
#define CIPHER_H

void encryptVigenere(const char *plaintext, const char *key, char *ciphertext);
void decryptVigenere(const char *ciphertext, const char *key, char *plaintext);

#endif // CIPHER_H