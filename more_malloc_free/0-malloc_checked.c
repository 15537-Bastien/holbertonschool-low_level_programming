#include "main.h"
#include <stdlib.h>

/**
 * malloc_checked - Alloue de la mémoire et vérifie l'allocation
 * @b: Nombre d'octets à allouer
 *
 * Return: Pointeur vers la mémoire allouée
 */
void *malloc_checked(unsigned int b)
{
    void *memoire;

    memoire = malloc(b);

    if (memoire == NULL)
    {
        exit(98);
    }

    return (memoire);
}
