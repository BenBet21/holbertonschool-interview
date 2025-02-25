#include "slide_line.h"

/**
 * slide_left - Slides and merges the line to the left
 * @line: Pointer to the array of integers
 * @size: Size of the array
 */
void slide_left(int *line, size_t size)
{
	size_t i, pos = 0;

		for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			if (pos != i)
			{
				line[pos] = line[i];
				line[i] = 0;
			}
			pos++;
		}
	}

		for (i = 0; i < size - 1; i++)
	{
		if (line[i] != 0 && line[i] == line[i + 1])
		{
			line[i] *= 2;
			line[i + 1] = 0;
		}
	}

	pos = 0;
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			if (pos != i)
			{
				line[pos] = line[i];
				line[i] = 0;
			}
			pos++;
		}
	}
}

/**
 * slide_right - Slides and merges the line to the right
 * @line: Pointer to the array of integers
 * @size: Size of the array
 */
void slide_right(int *line, size_t size)
{
	size_t i, pos = size - 1;

	/* Étape 1: Déplacer tous les nombres non nuls vers la droite */
	for (i = size; i > 0; i--)
	{
		if (line[i - 1] != 0)
		{
			if (pos != i - 1)
			{
				line[pos] = line[i - 1];
				line[i - 1] = 0;
			}
			pos--;
		}
	}

	/* Étape 2: Fusionner les nombres identiques */
	for (i = size - 1; i > 0; i--)
	{
		if (line[i] != 0 && line[i] == line[i - 1])
		{
			line[i] *= 2;
			line[i - 1] = 0;
		}
	}

		pos = size - 1;
	for (i = size; i > 0; i--)
	{
		if (line[i - 1] != 0)
		{
			if (pos != i - 1)
			{
				line[pos] = line[i - 1];
				line[i - 1] = 0;
			}
			pos--;
		}
	}
}

/**
 * slide_line - Slides and merges an array of integers
 * @line: Pointer to an array of integers
 * @size: Number of elements in the array
 * @direction: Direction to slide (SLIDE_LEFT or SLIDE_RIGHT)
 *
 * Return: 1 if successful, 0 otherwise
 */
int slide_line(int *line, size_t size, int direction)
{
	if (direction != SLIDE_LEFT && direction != SLIDE_RIGHT)
		return (0);

	if (direction == SLIDE_LEFT)
		slide_left(line, size);
	else
		slide_right(line, size);

	return (1);
}
