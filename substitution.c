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
char *cipher(char *plaintext, const char *key);

const int keyLength = 26;
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char const *argv[])
{
    // Check usage
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != keyLength)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    const char *key = argv[1];

    // Check key validity
    if (checkKeyValidity(key) == false)
    {
        printf("INVALID KEY\n");
        return 1;
    }

    // Get plaintext
    char *plaintext = get_string("plainttext: ");

    // Cipher text
    char *ciphertext = cipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    // Free memory allocated when cipher() was called
    free(ciphertext);

    return 0;
}

// Checks validity of given key
bool checkKeyValidity(const char *key)
{
    // Array is used to ensure each letter is used exactly once in the key
    bool lettersUsed[keyLength];

    // Set each element in the array to be false originally
    for (int i = 0; i < keyLength; i++)
    {
        lettersUsed[i] = false;
    }

    // Go through each character in the key
    for (int i = 0; i < keyLength; i++)
    {
        // Check for non alphabetic characters
        if (isalpha(key[i]) == 0)
        {
            printf("Key given contains a non alphabetic character\n");
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

// Ciphers a given string according to a given key and returns the resulting text
char *cipher(char *plaintext, const char *key)
{
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

    return ciphertext;
}
