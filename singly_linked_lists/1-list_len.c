#include "lists.h"

/**
 * list_len - Counts the nodes of a linked list
 * @h: Pointer to the first node
 *
 * Return: Number of nodes
 */
size_t list_len(const list_t *h)
{
	size_t compt = 0;

	while (h != NULL)
	{
		compt++;
		h = h->next;
	}
	return (compt);
}
