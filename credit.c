/*
    Author: Grant Lane
    Date: July 14, 2022
    Program that Takes a card number, checks if it is a valid number
    and then prints 1 of 3 card types: American Express ("AMEX"), Mastercard
    ("MASTERCARD"), or Visa ("VISA")
*/
#include <cs50.h>
#include <stdio.h>

int luhn_alg(int num);
bool is_valid_number(int number);
int get_last_digit(long number);
long remaining_digits(long number, int digit);
bool is_amex(int counter, int digit, bool amex);
bool is_master_card(int counter, int digit, bool mastercard, long number);
bool is_visa(int counter, int digit);
void print_card_type(bool visa, bool amex, bool master_card);

int main(void)
{
    long number;
    //Prompts the user to input a until it is a positve long
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    int counter = 0;
    int sum = 0;
    //Sets the card type's to false but can change later in the program
    bool amex = false;
    bool mastercard = false;
    bool visa = false;
    int digit;
    //Runs the Program that gets the sum of the numbers and gets the card type
    while (number > 0)
    {
        digit = get_last_digit(number);
        //check is reversed due to counter starting at 0
        if (counter % 2 == 0)
        {
            //for when the digit is at an odd in the card number
            sum += digit;
        }
        else
        {
            //for when the digit is at an even in the card number
            sum += luhn_alg(digit);
        }
        number = remaining_digits(number, digit);
        counter++;
        //Check the card type
        amex = is_amex(counter, digit, amex);
        mastercard = is_master_card(counter, digit, mastercard, number);

    }
    //Checks if the card type is visa
    visa = is_visa(counter, digit);
    bool is_real_card = is_valid_number(sum);
    if (is_real_card)
    {
        print_card_type(visa, amex, mastercard);
    }
    else
    {
        printf("INVALID\n");
    }
}

/*
Runs the Luhn's Algorithm for every other card number
*/
int luhn_alg(int num)
{
    int sum = 0;
    int product = 2 * num;
    //Calculates the sum of the digits in the product
    while (product > 0)
    {
        int digit = get_last_digit(product);
        sum += digit;
        product = remaining_digits(product, digit);
    }
    return sum;
}
/*
    Checks if the sum of the numbers is a product of 10
*/
bool is_valid_number(int number)
{
    return number % 10 == 0;
}

/*
    Gets the remainder digits of the card number
*/
long remaining_digits(long number, int digit)
{
    long remainder = number - digit;
    remainder /= 10;
    return remainder;
}

/*
    Gets the last digit of the card number
*/
int get_last_digit(long number)
{
    int digit = number % 10;
    return digit;
}

//Determines if the card is a american express
bool is_amex(int counter, int digit, bool amex)
{
    if (counter == 14 && (digit == 7 || digit == 4))
    {
        return true;
    }
    else if (counter == 15 && digit == 3 && amex)
    {
        return true;
    }
    return false;
}

//Determines if the card is a mastercard
bool is_master_card(int counter, int digit, bool mastercard, long number)
{
    if (counter == 15 && (digit >= 1 && digit <= 5) && number > 0)
    {
        return true;
    }
    else if (counter == 16 && digit == 5 && mastercard)
    {
        return true;
    }
    return false;
}

//Determines if the card is a visa
bool is_visa(int counter, int digit)
{
    if ((counter == 13 || counter == 16) && digit == 4)
    {
        return true;
    }
    return false;
}

/*
    Function that prints which card type the number belongs to
*/
void print_card_type(bool visa, bool amex, bool master_card)
{
    if (visa)
    {
        printf("VISA\n");
    }
    else if (amex)
    {
        printf("AMEX\n");
    }
    else if (master_card)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}