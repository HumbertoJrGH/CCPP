#include "vigenere.h"
#include <ctype.h>
#include <string.h>

void encryptVigenere(const char *plaintext, const char *key, char *ciphertext)
{
	int textLength = strlen(plaintext);
	int keyLength = strlen(key);
	int keyIndex = 0;

	for (int i = 0; i < textLength; i++)
		if (isalpha(plaintext[i]))
		{
			char base = islower(plaintext[i]) ? 'a' : 'A';
			char keyChar = islower(key[keyIndex % keyLength]) ? key[keyIndex % keyLength] - 'a' : key[keyIndex % keyLength] - 'A';
			ciphertext[i] = (plaintext[i] - base + keyChar) % 26 + base;
			keyIndex++;
		}
		else
			ciphertext[i] = plaintext[i];
	ciphertext[textLength] = '\0';
}

void decryptVigenere(const char *ciphertext, const char *key, char *plaintext)
{
	int textLength = strlen(ciphertext);
	int keyLength = strlen(key);
	int keyIndex = 0;

	for (int i = 0; i < textLength; i++)
		if (isalpha(ciphertext[i]))
		{
			char base = islower(ciphertext[i]) ? 'a' : 'A';
			char keyChar = islower(key[keyIndex % keyLength]) ? key[keyIndex % keyLength] - 'a' : key[keyIndex % keyLength] - 'A';
			plaintext[i] = (ciphertext[i] - base - keyChar + 26) % 26 + base;
			keyIndex++;
		}
		else
			plaintext[i] = ciphertext[i];
	plaintext[textLength] = '\0';
}