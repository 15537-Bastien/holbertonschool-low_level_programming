#include <stdio.h>

/**
 * main - Prints all single digit numbers using putchar
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int chiffre;

    for (chiffre = 0; chiffre <= 9; chiffre++)
    {
        putchar(chiffre + '0');
    }

    putchar('\n');

    return (0);
}
