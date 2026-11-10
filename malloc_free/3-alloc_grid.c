#include "main.h"
#include <stdlib.h>

/**
 * alloc_grid - Creates a 2D array of integers
 * @width: Number of columns
 * @height: Number of rows
 *
 * Return: Pointer to the grid or NULL on failure
 */
int **alloc_grid(int width, int height)
{
    int **grille;
    int ligne;
    int colonne;

    if (width <= 0 || height <= 0)
        return (NULL);

    grille = malloc(sizeof(int *) * height);
    if (grille == NULL)
        return (NULL);

    for (ligne = 0; ligne < height; ligne++)
    {
        grille[ligne] = malloc(sizeof(int) * width);
        if (grille[ligne] == NULL)
        {
            while (ligne > 0)
                free(grille[--ligne]);
            free(grille);
            return (NULL);
        }

        for (colonne = 0; colonne < width; colonne++)
            grille[ligne][colonne] = 0;
    }

    return (grille);
}
