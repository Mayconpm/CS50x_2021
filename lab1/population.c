#include <cs50.h>
#include <stdio.h>

int main(void)
{

    //Ask for the initial size for the population
    int initialSize;

    do
    {
        initialSize = get_int("Start size: ");
    } while (initialSize < 9);

    //Ask for the end size for the population
    int endSize;

    do
    {
        endSize = get_int("End size:");
    } while (endSize < initialSize);

    // Calculate number of years until we reach threshold

    int years = 0;
    int population = initialSize;
    int gain = 0;
    int lose = 0;

    while (population < endSize)
    {
        gain = population / 3;
        lose = population / 4;
        population = population + gain - lose;
        years++;
    }

    // Print number of years
    printf("Years: %d\n", years);
}