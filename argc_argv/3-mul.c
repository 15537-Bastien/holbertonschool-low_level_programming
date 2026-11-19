#include <stdio.h>
#include <stdlib.h>

/**
 * main - Multiplie deux nombres passes en arguments
 * @argc: Nombre d'arguments
 * @argv: Tableau des arguments
 *
 * Return: 0 en cas de succes, 1 en cas d'erreur
 */
int main(int argc, char *argv[])
{
	int nombre1;
	int nombre2;
	int resultat;

	if (argc != 3)
	{
		printf("Error\n");
		return (1);
	}

	nombre1 = atoi(argv[1]);
	nombre2 = atoi(argv[2]);

	resultat = nombre1 * nombre2;

	printf("%d\n", resultat);

	return (0);
}

