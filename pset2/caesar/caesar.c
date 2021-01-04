#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int encipher(string plaintext, int key);
int test_arguments(int arguments, string key[]);

int main(int argc, string argv[])
{
    int test = test_arguments(argc, argv);
    if (test)
    {
        return test;
    }
    else
    {
        string plaintext = get_string("plaintext: ");
        int key = atoi(argv[1]);
        return encipher(plaintext, key);
    }
}

int test_arguments(int arguments, string key[])
{
    if (arguments != 2)
    {
        printf("Usage: ./substitution key.\n");
        return 1;
    }
    for (int i = 0, n = strlen(key[1]); i < n; i++)
    {
        if (isalpha(key[1][i]))
        {
            printf("Usage: ./caesar key.\n");
            return 1;
        }
    }
    return 0;
}

int encipher(string plaintext, int key)
{
    printf("ciphertext: ");
    char ci;
    int n = strlen(plaintext);
    char ciphertext[n];
    for (int i = 0; i < n; i++)
    {
        int c = plaintext[i];

        if (isalpha(c))
        {
            ci = c + key % 26;
            bool test_boundaries = islower(ci) || isupper(ci);
            if (!test_boundaries)
            {
                ci -= 26;
            }
        }
        else
        {
            ci = c;
        }
        ciphertext[i] = ci;
    }
    printf("%s\n", ciphertext);
    return 0;
}