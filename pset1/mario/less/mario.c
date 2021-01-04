#include <stdio.h>
#include <cs50.h>

void draw(int height, int initial_height);

int main(void)
{
    int h;
    //Prompt user for height and keep doing it until a number between 1-8 is inserted
    do
    {
        h = get_int("What's is the height for the pyramid?(1-8) \n");
    } while (h < 1 || h > 8);

    draw(h, h);
}

void draw(int height, int initial_height)
{
    if (height == 0)
    {
        return;
    }
    draw(height - 1, initial_height);

    for (int i = 0; i < initial_height - height; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");
}