#include "dog.h"
#include <stdlib.h>

/**
 * new_dog - Creates a new dog
 * @name: Name of the dog
 * @age: Age of the dog
 * @owner: Name of the dog's owner
 *
 * Return: Pointer to the new dog, or NULL on failure
 */

dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *chien;
	int longueur_nom = 0, longueur_owner = 0;
	int i;

	if (name == NULL || owner == NULL)
		return (NULL);

	while (name[longueur_nom] != '\0')
		longueur_nom++;

	while (owner[longueur_owner] != '\0')
		longueur_owner++;

	chien = malloc(sizeof(dog_t));
	if (chien == NULL)
		return (NULL);

	chien->name = malloc(longueur_nom + 1);
	if (chien->name == NULL)
	{
		free(chien);
		return (NULL);
	}

	chien->owner = malloc(longueur_owner + 1);
	if (chien->owner == NULL)
	{
		free(chien->name);
		free(chien);
		return (NULL);
	}

	for (i = 0; i <= longueur_nom; i++)
		chien->name[i] = name[i];

	for (i = 0; i <= longueur_owner; i++)
		chien->owner[i] = owner[i];

	chien->age = age;

	return (chien);
}


