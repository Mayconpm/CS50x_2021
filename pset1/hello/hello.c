#include <stdio.h>
#include<cs50.h>

int main(void)
{
    //Gets the name from the user
    string name = get_string("What's your name?\n");

    //Prints out the salutation plus te name
    printf("\nHello, %s!\n", name);
}