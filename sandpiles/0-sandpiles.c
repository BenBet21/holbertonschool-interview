#include <stdio.h>

/**
 * print_grid - Prints a 3x3 grid
 * @grid: The grid to print
 */
void print_grid(int grid[3][3])
{
	int i, j;

	printf("=\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d", grid[i][j]);
			if (j < 2)
				printf(" ");
		}
		printf("\n");
	}
}

/**
 * add_grids - Adds two 3x3 grids and stores the result in grid1
 * @grid1: The first grid (result is stored here)
 * @grid2: The second grid
 */
void add_grids(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid1[i][j] += grid2[i][j];
		}
	}
}

/**
 * is_stable - Checks if a grid is stable (no cell > 3)
 * @grid: The grid to check
 * Return: 1 if stable, 0 otherwise
 */
int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
				return (0);
		}
	}
	return (1);
}

/**
 * topple - Performs a toppling on an unstable grid
 * @grid: The grid to topple
 */
void topple(int grid[3][3])
{
	int i, j;
	int temp[3][3] = {0}; /* Temporary grid initialized to 0 */

	/* Identify unstable cells and distribute grains */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				temp[i][j] -= 4;
				if (i > 0)
					temp[i - 1][j] += 1;
				if (i < 2)
					temp[i + 1][j] += 1;
				if (j > 0)
					temp[i][j - 1] += 1;
				if (j < 2)
					temp[i][j + 1] += 1;
			}
		}
	}

	/* Apply the toppling changes to the original grid */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid[i][j] += temp[i][j];
		}
	}
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles and stabilizes grid1
 * @grid1: The first sandpile (result is stored here)
 * @grid2: The second sandpile
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	/* Step 1: Add both grids */
	add_grids(grid1, grid2);

	/* Step 2: Stabilize the sandpile */
	while (!is_stable(grid1))
	{
		print_grid(grid1);
		topple(grid1);
	}
}
