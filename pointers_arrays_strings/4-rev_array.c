#include "main.h"

/**
 * reverse_array - Reverses an array of integers
 * @a: Array of integers
 * @n: Number of elements in the array
 *
 * Return: Nothing
 */
void reverse_array(int *a, int n)
{
	int i = 0;
	int j = n - 1;
	int temp;

	while (i < j)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		i++;
		j--;
	}
}
