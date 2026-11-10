#include "main.h"
#include <stdlib.h>

/**
 * create_array - Creates an array of chars
 * @size: Number of elements
 * @c: Character used to initialize the array
 *
 * Return: Pointer to the array or NULL
 */
char *create_array(unsigned int size, char c)
{
    char *tab;
    unsigned int i;

    if (size == 0)
    {
        return (NULL);
    }

    tab = malloc(sizeof(char) * size);

    if (tab == NULL)
    {
        return (NULL);
    }

    i = 0;

    while (i < size)
    {
        tab[i] = c;
        i++;
    }

    return (tab);
}
