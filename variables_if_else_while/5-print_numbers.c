#include <stdio.h>

/**
 * main - Prints all single digit numbers
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int chiffre;

    for (chiffre = 0; chiffre <= 9; chiffre++)
    {
        printf("%d", chiffre);
    }

    printf("\n");

    return (0);
}
