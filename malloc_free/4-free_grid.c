#include "main.h"
#include <stdlib.h>

/**
 * free_grid - Frees a 2D array of integers
 * @grid: Pointer to the grid
 * @height: Number of rows
 *
 * Return: Nothing
 */
void free_grid(int **grid, int height)
{
    int indice_ligne;

    if (grid == NULL)
        return;

    for (indice_ligne = 0; indice_ligne < height; indice_ligne++)
    {
        free(grid[indice_ligne]);
    }

    free(grid);
}

