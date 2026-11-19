#include <stddef.h>
#include "function_pointers.h"

/**
 * int_index - Searches for an integer using a comparison function
 * @array: Pointer to the array of integers
 * @size: Number of elements in the array
 * @cmp: Pointer to the comparison function
 *
 * Return: Index of the first matching element, or -1
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int indice;

	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	for (indice = 0; indice < size; indice++)
	{
		if (cmp(array[indice]) != 0)
		{
			return (indice);
		}
	}

	return (-1);
}
