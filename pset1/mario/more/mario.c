#include <stdio.h>
#include <cs50.h>

int height;
int direction = 0;

int main(void)
{
    do //Prompt user for height and keep doing it until a number between 1-8 is inserted
    {
        height = get_int("What's is the height?(1-8) ");
    }
    while (height < 1 || height > 8);

    //Iterate from 1 through height
    for (int i = 0; i < height; i++)
    {
        //On iteration i, print i hashes generating pyramid
        for (int j = height - 1; j >= 0; j --)
        {
            if (j <= i)
            {
                printf("#");
            }
            else if (j > i && direction == 0)
            {
                printf(" ");
            }
            //Changes the direction to create the pyramid on the right
            if (j <= 0 && direction == 0)
            {
                printf("  ");
                direction = 1;
                j = height;
            }
        }
        direction = 0;
        printf("\n");
    }
}