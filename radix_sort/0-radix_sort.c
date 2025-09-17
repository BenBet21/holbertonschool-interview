#include "sort.h"
#include <stdlib.h>

/**
 * get_max - Finds the maximum value in an array
 * @array: Pointer to the array
 * @size: Number of elements in the array
 *
 * Return: The largest value found
 */
static int get_max(int *array, size_t size)
{
	size_t i;
	int max = array[0]; /* On suppose que le 1erélément est le +gd au départ */

	for (i = 1; i < size; i++)
	{
		if (array[i] > max) /* Si on trouve un élément +gd on maj max */
			max = array[i];
	}
	return (max);
}

/**
 * counting_sort_radix - Counting sort for a specific digit (exp)
 * @array: Pointer to the array to sort
 * @size: Number of elements in the array
 * @exp: Exponent indicating the digit to sort (1 = units, 10 = tens, ...)
 *
 * Implements a stable counting sort for the digit at exp.
 */
static void counting_sort_radix(int *array, size_t size, int exp)
{
	int *output, count[10] = {0};
	size_t i;

	output = malloc(sizeof(int) * size);
	if (!output)
		return;

	for (i = 0; i < size; i++)
		count[(array[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = size; i > 0; i--)
	{
		output[count[(array[i - 1] / exp) % 10] - 1] = array[i - 1];
		count[(array[i - 1] / exp) % 10]--;
	}

	for (i = 0; i < size; i++)
		array[i] = output[i];

	free(output);
}

/**
 * radix_sort - Sorts an array of integers using LSD Radix Sort
 * @array: Pointer to the array to sort
 * @size: Number of elements in the array
 *
 * Sorts the array in ascending order using the Radix Sort algorithm.
 */
void radix_sort(int *array, size_t size)
{
	int max, exp;

	if (!array || size < 2)
		return;

	max = get_max(array, size);
	for (exp = 1; max / exp > 0; exp *= 10)
	{
		counting_sort_radix(array, size, exp);
		print_array(array, size);
	}
}
