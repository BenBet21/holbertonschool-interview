#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

static void merge_sort_recursive(int *array, int *aux, size_t left,
		size_t right);
static void merge_sort_merge(int *array, int *aux, size_t left, size_t mid,
		size_t right);

/**
 * merge_sort - Trie un tableau d'entiers en ordre croissant
 * en utilisant l'algorithme Merge Sort (top-down)
 * @array: Le tableau à trier
 * @size: Nombre d'éléments dans @array
 */
void merge_sort(int *array, size_t size)
{
	int *aux;

	if (!array || size < 2)
		return;

	aux = malloc(sizeof(int) * size);
	if (!aux)
		return;

	merge_sort_recursive(array, aux, 0, size);

	free(aux);
}

/**
 * merge_sort_recursive - Trie récursivement les sous-tableaux
 * par la méthode du tri fusion (top-down)
 * @array: Le tableau principal à trier
 * @aux:   Tableau auxiliaire temporaire pour la fusion
 * @left:  Indice de début du sous-tableau (inclus)
 * @right: Indice de fin du sous-tableau (exclus)
 */
static void merge_sort_recursive(int *array, int *aux, size_t left,
		size_t right)
{
	size_t mid;

	if (right - left < 2)
		return;

	mid = left + (right - left) / 2;

	merge_sort_recursive(array, aux, left, mid);
	merge_sort_recursive(array, aux, mid, right);
	merge_sort_merge(array, aux, left, mid, right);
}

/**
 * merge_sort_merge - Merge two sorted halves and print the merge state
 * @array: The array to sort
 * @aux: Temporary array used to merge values
 * @left: Start index of the left half
 * @mid: Start index of the right half
 * @right: End index of the right half
 */
static void merge_sort_merge(int *array, int *aux, size_t left, size_t mid,
		size_t right)
{
	size_t i, j, k;

	printf("Merging...\n");
	printf("[left]: ");
	print_array(array + left, mid - left);
	printf("[right]: ");
	print_array(array + mid, right - mid);
	i = left;
	j = mid;
	k = left;
	while (i < mid && j < right)
	{
		if (array[i] <= array[j])
			aux[k++] = array[i++];
		else
			aux[k++] = array[j++];
	}
	while (i < mid)
		aux[k++] = array[i++];
	while (j < right)
		aux[k++] = array[j++];
	for (k = left; k < right; k++)
		array[k] = aux[k];
	printf("[Done]: ");
	print_array(array + left, right - left);
}
