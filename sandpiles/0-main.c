#include "sandpiles.h"
#include <stdlib.h>

/**
 * print_grid_sum - Prints two 3x3 grids side by side
 * @grid1: Left 3x3 grid
 * @grid2: Right 3x3 grid
 */
static void print_grid_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid1[i][j]);
		}

		printf(" %c ", (i == 1 ? '+' : ' '));

		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid2[i][j]);
		}
		printf("\n");
	}
}

static void print_grid(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}
/**
 * main - Entry point, tests the sandpiles_sum function
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	int grid1[3][3] = {
		{3, 3, 3},
		{3, 3, 3},
		{3, 3, 3}
	};

	int grid2[3][3] = {
		{1, 3, 1},
		{3, 3, 3},
		{1, 3, 1}
	};

	print_grid_sum(grid1, grid2);
	sandpiles_sum(grid1, grid2);

	printf("=\n");
	print_grid(grid1);

	return (EXIT_SUCCESS);
}
