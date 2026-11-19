#include <stddef.h>
#include "function_pointers.h"

/**
 * print_name - Prints a name using a function pointer
 * @name: Name to print
 * @f: Pointer to the function that prints the name
 *
 * Return: Nothing
 */
void print_name(char *name, void (*f)(char *))
{
	if (f != NULL)
	{
		f(name);
	}
}
