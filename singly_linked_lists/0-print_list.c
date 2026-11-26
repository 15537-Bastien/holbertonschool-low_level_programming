#include <stdio.h>
#include "lists.h"

/**
 * print_list - Prints all nodes of a linked list
 * @h: Pointer to the first node
 *
 * Return: Number of nodes
 */
size_t print_list(const list_t *h)
{
	size_t compteur = 0;

	while (h != NULL)
	{
		if (h->str == NULL)
			printf("[0] (nil)\n");
		else
			printf("[%u] %s\n", h->len, h->str);

		compteur++;
		h = h->next;
	}
	return (compteur);
}
