#include "main.h"
#include <stdlib.h>

/**
 * _calloc - Allocates memory for an array using malloc
 * @nmemb: Number of elements
 * @size: Size of each element in bytes
 *
 * Return: Pointer to allocated memory, or NULL on failure
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	unsigned char *memoire;
	size_t total;
	size_t i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	total = (size_t)nmemb * size;

	if (total / nmemb != size)
		return (NULL);

	memoire = malloc(total);
	if (memoire == NULL)
		return (NULL);

	for (i = 0; i < total; i++)
		memoire[i] = 0;

	return (memoire);
}

