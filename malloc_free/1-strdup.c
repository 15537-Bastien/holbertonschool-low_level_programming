#include "main.h"
#include <stdlib.h>

/**
 * _strdup - Duplicates a string in newly allocated memory
 * @str: String to duplicate
 *
 * Return: Pointer to duplicated string or NULL
 */
char *_strdup(char *str)
{
    char *copie;
    int len = 0;
    int i = 0;

    if (str == NULL)
    {
        return (NULL);
    }

    while (str[len] != '\0')
    {
        len++;
    }

    copie = malloc(sizeof(char) * (len + 1));

    if (copie == NULL)
    {
        return (NULL);
    }

    while (i < len)
    {
        copie[i] = str[i];
        i++;
    }

    copie[i] = '\0';

    return (copie);
}
