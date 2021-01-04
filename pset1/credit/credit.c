#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long card_number;
    int get_digit;
    int count_digits = 0;
    int other_digit;
    int other_sum = 0;
    long start_number = 0;
    int checksum = 0;
    bool visa_digits;
    bool amex_start;
    bool mastercard_start;

    //Get the card number
    card_number = get_long("What's is you credit card card_number? ");
    //Run the loop while there are numbers on the card
    while (card_number != 0)
    {
        //Get the last digit
        get_digit = card_number % 10;

        //Separete the other digits
        if (count_digits % 2 != 0)
        {
            //Multiply the other digit by two
            other_digit = get_digit * 2;

            //If the multiplication gets 2 digits than sum the digits
            other_sum += (other_digit % 100 == 0) ? other_digit :
                         other_digit % 10 + other_digit / 10;
        }
        else
        {
            //Sum of the digits that weren’t multiplied by 2
            checksum += get_digit;
        }
        //Get's the start number
        if (card_number / 100 == 0 && start_number == 0)
        {
            start_number = card_number;
        }

        //Eliminate the last digit from the card numbem then increment the count
        card_number = card_number / 10;
        count_digits++;
    }
    //Get checksum las digit
    checksum = (checksum + other_sum) % 10;

    //Check the condition for each card then print
    visa_digits = count_digits == 13 || count_digits == 16;

    amex_start = start_number == 34 || start_number == 37;

    mastercard_start = start_number == 51 || start_number == 52 || start_number == 53 ||
                       start_number == 54 || start_number == 55;

    if (checksum == 0 && count_digits == 15 && amex_start)
    {
        printf("AMEX\n");
    }
    else if (checksum == 0 && start_number / 10 == 4 && visa_digits)
    {
        printf("VISA\n");
    }
    else if (checksum == 0 && count_digits == 16 && mastercard_start)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}