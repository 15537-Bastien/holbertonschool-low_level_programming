#include "main.h"
#include <stdlib.h>

/**
 * str_concat - Concatenates two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: Pointer to new string or NULL
 */
char *str_concat(char *s1, char *s2)
{
    char *resultat;
    int len1 = 0;
    int len2 = 0;
    int i = 0;
    int j = 0;

    if (s1 != NULL)
    {
        while (s1[len1] != '\0')
        {
            len1++;
        }
    }

    if (s2 != NULL)
    {
        while (s2[len2] != '\0')
        {
            len2++;
        }
    }

    resultat = malloc(sizeof(char) * (len1 + len2 + 1));

    if (resultat == NULL)
    {
        return (NULL);
    }

    while (i < len1)
    {
        resultat[i] = s1[i];
        i++;
    }

    while (j < len2)
    {
        resultat[i] = s2[j];
        i++;
        j++;
    }

    resultat[i] = '\0';

    return (resultat);
}
