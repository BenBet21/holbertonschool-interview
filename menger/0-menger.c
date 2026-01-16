#include "menger.h"
#include <stdio.h>
#include <math.h>

/**
 * is_hole - Determines if a given position should be a "hole"
 *           in the Menger sponge
 * @i: Row position
 * @j: Column position
 *
 * Return: 1 if the position is a hole, 0 otherwise
 */
int is_hole(int i, int j)
{
	while (i > 0 || j > 0)
	{
		if (i % 3 == 1 && j % 3 == 1)
			return (1);

		i /= 3;
		j /= 3;
	}

	return (0);
}

/**
 * print_row - Prints a single row of the Menger sponge
 * @row: The row index
 * @size: The size of the sponge
 */
void print_row(int row, int size)
{
	int j;

	for (j = 0; j < size; j++)
	{
		if (is_hole(row, j))
			printf(" ");
		else
			printf("#");
	}
	printf("\n");
}

/**
 * menger - Draws a 2D Menger sponge
 * @level: The level of the Menger sponge
 *
 * Description:
 * - The level determines the size of the grid: 3^level
 * - Each position is tested to see if it's a hole or not
 * - Holes are displayed with a space ' '
 * - Solid parts are displayed with '#'
 */
void menger(int level)
{
	int size;
	int i;

	if (level < 0)
		return;

	size = pow(3, level);

	for (i = 0; i < size; i++)
	{
		print_row(i, size);
	}
}
