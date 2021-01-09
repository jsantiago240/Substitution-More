/* Javius Santiago
 * 1/8/2021
 * Substitution2.c - This program uses a given key to cipher or decipher text
 * using substitution
 */

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Prototypes
bool checkKeyValidity(const char *key);
int getIndex(const char *str, char element);
void cipher(const char *key);
void decipher(const char *key);

const int keyLength = 26;
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char const *argv[])
{
    // Check usage
    if (argc != 3)
    {
        printf("Usage: ./substitution [C]ipher/[D]ecipher key\n");
        return 1;
    }

    // Check key validity
    const char *key = argv[2];
    if (checkKeyValidity(key) == false)
    {
        return 1;
    }

    // Cipher or Decipher based on users choice
    if (strcasecmp(argv[1], "cipher") == 0 || strcasecmp(argv[1], "c") == 0)
    {
        cipher(key);
    }
    else if (strcasecmp(argv[1], "decipher") == 0 || strcasecmp(argv[1], "d") == 0)
    {
        decipher(key);
    }
    else
    {
        printf("Usage: ./substitution [C]ipher/[D]ecipher key\n");
        return 1;
    }

    return 0;
}

// Checks validity of given key
bool checkKeyValidity(const char *key)
{
    // Array is used to ensure each letter is used exactly once in the key
    bool lettersUsed[keyLength];

    // Ensure key length is correct
    if (strlen(key) != keyLength)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // Set each element in the array to be false originally
    for (int i = 0; i < keyLength; i++)
    {
        lettersUsed[i] = false;
    }

    // Traverse each character in the key
    for (int i = 0; i < keyLength; i++)
    {
        // Check for non alphabetic characters
        if (isalpha(key[i]) == 0)
        {
            printf("Key given contains a non alphabetic character: %c\n", key[i]);
            return false;
        }

        // Check each letter is used once
        if (lettersUsed[getIndex(alphabet, key[i])] == true)
        {
            printf("%c is used more than once in the key\n", key[i]);
            return false;
        }

        lettersUsed[getIndex(alphabet, key[i])] = true;
    }

    return true;
}

// Returns the index of a desired character within a string, -1 if not found
int getIndex(const char *str, char element)
{
    for (int i = 0; i < strlen(str); i++)
    {
        // If found, return the index
        if (tolower(str[i]) == tolower(element))
        {
            return i;
        }
    }

    // If not found return -1
    return -1;
}

// Ciphers a given string according to a given key
void cipher(const char *key)
{
    // Get plaintext
    char *plaintext = get_string("plaintext: \t");

    char *ciphertext = malloc(sizeof(plaintext));

    // Loops through each char in the string (including the null terminating character)
    for (int i = 0; i < strlen(plaintext) + 1; i++)
    {
        // If current char is uppercase and a letter
        if (isupper(plaintext[i]) != 0 && isalpha(plaintext[i]) != 0)
        {
            // Set current char equal to uppercase version of corresponding letter
            ciphertext[i] = toupper(key[getIndex(alphabet, plaintext[i])]);
        }
        // Else if current char is a letter but NOT uppercase
        else if (isalpha(plaintext[i]) != 0)
        {
            // Set current char equal to lowercase version of corresponding letter
            ciphertext[i] = tolower(key[getIndex(alphabet, plaintext[i])]);
        }
        // Else if current char is not a letter
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: \t%s\n", ciphertext);
    free(ciphertext);
}

// Deciphers a given string according to a given key
void decipher(const char *key)
{
    // Get ciphertext from user
    char *ciphertext = get_string("ciphertext: \t");

    char *plaintext = malloc(sizeof(ciphertext));

    // Loops through each char in the string (including the null terminating character)
    for (int i = 0; i < strlen(ciphertext) + 1; i++)
    {
        // If current char is a letter and uppercase
        if (isupper(ciphertext[i]) != 0 && isalpha(ciphertext[i]) != 0)
        {
            // Set plaintext[i] equal to uppercase version of corresponding char
            plaintext[i] = toupper(alphabet[getIndex(key, ciphertext[i])]);
        }
        // Else if current char is a letter but not uppercase
        else if (isalpha(ciphertext[i]) != 0)
        {
            // Set plaintext[i] equal to lowercase version of corresponding char
            plaintext[i] = tolower(alphabet[getIndex(key, ciphertext[i])]);
        }
        // Else if current char is not a letter
        else
        {
            // Copy the char as it is
            plaintext[i] = ciphertext[i];
        }
    }

    printf("plaintext: \t%s\n", plaintext);
    free(plaintext);
}
