#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node - Adds a new node at the beginning of a linked list
 * @head: Pointer to the head pointer of the list
 * @str: String to duplicate
 *
 * Return: Address of the new node, or NULL on failure
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *nouveau;
	unsigned int longueur = 0;

	if (head == NULL || str == NULL)
		return (NULL);

	nouveau = malloc(sizeof(list_t));
	if (nouveau == NULL)
		return (NULL);

	nouveau->str = strdup(str);
	if (nouveau->str == NULL)
	{
		free(nouveau);
		return (NULL);
	}

	while (str[longueur] != '\0')
		longueur++;

	nouveau->len = longueur;
	nouveau->next = *head;
	*head = nouveau;

	return (nouveau);
}
