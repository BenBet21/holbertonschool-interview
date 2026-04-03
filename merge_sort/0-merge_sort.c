#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

static void merge_sort_recursive(int *array, int *aux, size_t left,
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

	/* Cas de base : tableau vide ou d'un seul élément, rien à faire */
	if (!array || size < 2)
		return;

	/* Unique malloc autorisé : on alloue un tableau auxiliaire
	 * de la même taille que l'original, utilisé pour les fusions */
	aux = malloc(sizeof(int) * size);
	if (!aux)
		return;

	/* Lancement du tri récursif sur tout le tableau [0, size) */
	merge_sort_recursive(array, aux, 0, size);

	/* Unique free : libération du tableau auxiliaire */
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
	size_t n = right - left; /* Taille du sous-tableau courant */
	size_t mid, i, j, k;

	/* Cas de base : un seul élément est déjà trié, on remonte */
	if (n < 2)
		return;

	/* Calcul du milieu : la moitié gauche est toujours <= droite
	 * Ex: {1,2,3,4,5} → left={1,2} (taille 2), right={3,4,5} (taille 3)
	 * n/2 arrondi vers le bas garantit que left <= right */
	mid = left + n / 2;

	/* Récursion sur la moitié GAUCHE [left, mid) EN PREMIER */
	merge_sort_recursive(array, aux, left, mid);

	/* Récursion sur la moitié DROITE [mid, right) ensuite */
	merge_sort_recursive(array, aux, mid, right);

	/* --- FUSION des deux moitiés triées --- */

	/* Affichage de l'état avant fusion (requis par l'exercice) */
	printf("Merging...\n");
	printf("[left]: ");
	print_array(array + left, mid - left);
	printf("[right]: ");
	print_array(array + mid, right - mid);

	/* i parcourt la moitié gauche  [left, mid)
	 * j parcourt la moitié droite  [mid, right)
	 * k est l'indice d'écriture dans aux */
	i = left;
	j = mid;
	k = left;

	/* Comparaison élément par élément : on prend le plus petit
	 * et on l'écrit dans aux, jusqu'à épuisement d'une des moitiés */
	while (i < mid && j < right)
	{
		if (array[i] <= array[j])
			aux[k++] = array[i++]; /* Élément gauche plus petit ou égal */
		else
			aux[k++] = array[j++]; /* Élément droit plus petit */
	}

	/* Recopie des éléments restants de la moitié gauche (si elle n'est pas épuisée) */
	while (i < mid)
		aux[k++] = array[i++];

	/* Recopie des éléments restants de la moitié droite (si elle n'est pas épuisée) */
	while (j < right)
		aux[k++] = array[j++];

	/* Recopie du résultat fusionné (dans aux) vers le tableau original
	 * uniquement sur la portion [left, right) concernée */
	for (k = left; k < right; k++)
		array[k] = aux[k];

	/* Affichage du résultat après fusion */
	printf("[Done]: ");
	print_array(array + left, n);
}
