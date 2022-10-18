#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)                      // Checks that a single argument exists.
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int key_len = strlen(key);
    string ref = "abcdefghijklmnopqrstuvwxyz";      // Creates reference alphabet to map against key.


    if (key_len != 26)                  //  Checks that key length = 26.
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    int diff[26];

    for (int i = 0; i < key_len; i++)           // Calculates difference between reference and key strings.
    {
        key[i] = tolower(key[i]);               // Sets key to lowercase.

        for (int j = 0; j < i ; j++)
        {
            if (key[i] == key[j])               // Checks for repeated characters.
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

        if (isalpha(key[i]) == 0)       // Checks key for non alphabetic characters.
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        diff[i] = (int)key[i] - (int)ref [i];   // Calculates by how much each letter should shift according to key.
    }

    string plain = get_string("Plaintext: ");           // Takes user plaintext input.
    int n = strlen(plain);
    string cipher = plain;                              // Initialises ciphertext string.

    for (int i = 0; i < n; i++)                         // Runs through each letter of plain text.
    {
        for (int j = 0; j < key_len; j++)               // Matches plaintext letter to reference alphabet.
        {
            if ((int)tolower(plain[i]) == (int)ref[j])
            {
                cipher[i] = (int)cipher[i] + diff[j];   // Shifts letter according to calculated difference to output new ciphertext.
                break;
            }
        }
    }
    printf("ciphertext: %s\n", cipher);         // Prints ciphertext.

    return 0;
}