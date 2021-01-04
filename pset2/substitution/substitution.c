#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int test_arguments(int arguments, string key[]);
int encipher(string plaintext, string key);


int main(int argc, string argv[])
{
    //Call the function responsible to test the arguments
    if (test_arguments(argc, argv))
    {
        return 1;
    }
    else
    {
        //Encipher the text
        string key = argv[1];
        string text = get_string("plaintext: ");
        // encipher(text, key);
        return encipher(text, key);
    }

}


int test_arguments(int arguments, string key[])
{
    if (arguments != 2)
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
    else if (strlen(key[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(key[1]); i < n; i++)
    {
        char i_char = key[1][i];
        if (!isalpha(i_char))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        for (int j = 0; j < n; j++)
        {
            char j_char = key[1][j];
            if (toupper(i_char) == toupper(j_char) && i != j)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    return 0;
}


int encipher(string text, string key)
{
    int value;
    char ci;
    int n = strlen(text);
    char ciphertext[n];

    for (int i = 0; i < n; i++)
    {
        char c = text[i];
        bool alphanumeric = isalpha(text[i]);

        if (alphanumeric && isupper(c))
        {
            value = c - 65;
            ci = toupper(key[value]);
        }
        else if (alphanumeric && islower(c))
        {
            value = c - 97;
            ci = tolower(key[value]);
        }
        else
        {
            ci = c;
        }
        ciphertext[i] = ci;
    }
    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}