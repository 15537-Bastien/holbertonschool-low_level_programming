#include <stdio.h>
#include <stdlib.h>

/**
 * main - Additionne les nombres positifs passes en arguments
 * @argc: Nombre d'arguments
 * @argv: Tableau des arguments
 *
 * Return: 0 en cas de succes, 1 en cas d'erreur
 */
int main(int argc, char *argv[])
{
	int somme = 0;
	int i;
	int j;

	for (i = 1; i < argc; i++)
	{
		for (j = 0; argv[i][j] != '\0'; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}
		}
		somme += atoi(argv[i]);
	}

	printf("%d\n", somme);

	return (0);
}

