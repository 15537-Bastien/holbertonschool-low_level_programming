#include <stddef.h>
#include "function_pointers.h"

/**
 * array_iterator - Executes a function on each array element
 * @array: Pointer to the array
 * @size: Number of elements in the array
 * @action: Pointer to the function to execute
 *
 * Return: Nothing
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t indice;

	if (array == NULL || action == NULL)
		return;

	for (indice = 0; indice < size; indice++)
	{
		action(array[indice]);
	}
}
