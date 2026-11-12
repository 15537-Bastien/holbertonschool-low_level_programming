#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - Concatene deux chaines
 * @s1: Premiere chaine
 * @s2: Deuxieme chaine
 * @n: Nombre maximal de caracteres de s2
 *
 * Return: Pointeur vers la nouvelle chaine ou NULL
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
    unsigned int longueur1 = 0;
    unsigned int longueur2 = 0;
    unsigned int indice = 0;
    unsigned int indice2 = 0;
    char *resultat;

    if (s1 != NULL)
    {
        while (s1[longueur1] != '\0')
        {
            longueur1++;
        }
    }

    if (s2 != NULL)
    {
        while (s2[longueur2] != '\0')
        {
            longueur2++;
        }
    }

    if (n < longueur2)
    {
        longueur2 = n;
    }

    resultat = malloc(longueur1 + longueur2 + 1);

    if (resultat == NULL)
    {
        return (resultat);
    }

    while (indice < longueur1)
    {
        resultat[indice] = s1[indice];
        indice++;
    }

    while (indice2 < longueur2)
    {
        resultat[indice] = s2[indice2];
        indice2++;
        indice++;
    }

    resultat[indice] = '\0';

    return (resultat);
}
