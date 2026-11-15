#ifndef DOG_H
#define DOG_H


void init_dog(struct dog *d, char *name, float age, char *owner)
{
    /* Instructions de la fonction */
}
/**
 * struct dog - Structure representing a dog
 * @name: Name of the dog
 * @age: Age of the dog
 * @owner: Name of the dog's owner
 */

struct dog
{
	char *name;
	float age;
	char *owner;
};

#endif /* DOG_H */
