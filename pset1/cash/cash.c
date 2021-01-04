#include <stdio.h>
#include <math.h>
#include <cs50.h>

float dollars;
int coins = 0;

int main(void)
{
    //Prompt user for Cash owed and keep doing it until a positive number received
    do
    {
        dollars = get_float("Cash owed: ");
    }
    while (dollars <= 0);

    //Round the cents to the nearest penny
    int cents = round(dollars * 100);

    //Iterate deducting the values from the bigger to the smaller
    while (cents > 0)
    {
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents --;
        }
        coins++;
    }
    //Print the minimal amount of coins
    printf("%i\n", coins);
}