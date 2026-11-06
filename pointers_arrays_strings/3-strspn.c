#include "main.h"

/**
 * _strspn - Gets the length of a prefix substring
 * @s: String to examine
 * @accept: String containing accepted characters
 *
 * Return: Number of accepted bytes at the beginning of s
 */
unsigned int _strspn(char *s, char *accept)
{
    int i = 0;
    int j = 0;

    while (s[i] != '\0')
    {
        j = 0;

        while (accept[j] != '\0')
        {
            if (s[i] == accept[j])
            {
                break;
            }

            j++;
        }

        if (accept[j] == '\0')
        {
            break;
        }

        i++;
    }

    return (i);
}
