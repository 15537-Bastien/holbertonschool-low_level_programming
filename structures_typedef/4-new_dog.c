#include "dog.h"
#include <stdlib.h>
#include <string.h>

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

	chien = malloc(sizeof(dog_t));
	if (chien == NULL)
		return (NULL);

	chien->name = strdup(name);
	if (chien->name == NULL)
	{
		free(chien);
		return (NULL);
	}

	chien->owner = strdup(owner);
	if (chien->owner == NULL)
	{
		free(chien->name);
		free(chien);
		return (NULL);
	}

	chien->age = age;

	return (chien);
}

