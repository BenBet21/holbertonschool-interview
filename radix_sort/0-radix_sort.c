#include "sort.h"
#include <stdlib.h> /* Nécessaire pour malloc et free */

/**
 * get_max - Trouve la valeur maximale dans un tableau
 * @array: pointeur vers le tableau d'entiers
 * @size: nombre d'éléments dans le tableau
 * Return: la plus grande valeur trouvée
 *
 * Cette fonction parcourt le tableau pour identifier l'élément le plus grand.
 * Elle est utilisée dans l'algorithme Radix Sort afin de savoir jusqu'à
 * quel chiffre il faut trier.
 */
static int get_max(int *array, size_t size)
{
	size_t i;
	int max = array[0]; /* On suppose que le premier élément est le plus grand au départ */

	for (i = 1; i < size; i++)
	{
		if (array[i] > max) /* Si on trouve un élément plus grand, on met à jour max */
			max = array[i];
	}
	return (max);
}

/**
 * counting_sort_radix - Trie le tableau en fonction d'un chiffre précis (exposant)
 * @array: pointeur vers le tableau à trier
 * @size: nombre d'éléments dans le tableau
 * @exp: exposant indiquant le chiffre à trier (1 = unités, 10 = dizaines, etc.)
 *
 * Cette fonction implémente un tri par comptage (Counting Sort) mais appliqué
 * uniquement sur un chiffre précis (par exemple, d'abord les unités, puis les dizaines...).
 * Cela permet de trier progressivement sans comparer directement les nombres.
 */
static void counting_sort_radix(int *array, size_t size, int exp)
{
	int *output, count[10] = {0}; /* count[] garde le nombre d'occurrences de chaque chiffre (0 à 9) */
	size_t i;

	output = malloc(sizeof(int) * size);
	if (!output)
		return; /* Si l'allocation échoue, on quitte la fonction */

	/* Comptage du nombre d'occurrences pour chaque chiffre à la position exp */
	for (i = 0; i < size; i++)
		count[(array[i] / exp) % 10]++;

	/* Transformation du comptage en positions cumulées (tableau d'index) */
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	/* Construction du tableau trié (de droite à gauche pour garantir la stabilité du tri) */
	for (i = size; i > 0; i--)
	{
		output[count[(array[i - 1] / exp) % 10] - 1] = array[i - 1];
		count[(array[i - 1] / exp) % 10]--;
	}

	/* Copie du résultat trié dans le tableau original */
	for (i = 0; i < size; i++)
		array[i] = output[i];

	free(output); /* Libération de la mémoire temporaire */
}

/**
 * radix_sort - Trie un tableau d'entiers avec l'algorithme Radix Sort (LSD)
 * @array: pointeur vers le tableau à trier
 * @size: nombre d'éléments dans le tableau
 *
 * L'algorithme LSD (Least Significant Digit) Radix Sort commence par trier
 * selon le chiffre le moins significatif (unités), puis passe aux dizaines,
 * centaines, etc. Cela permet un tri efficace pour des entiers positifs.
 */
void radix_sort(int *array, size_t size)
{
	int max, exp;

	if (!array || size < 2)
		return; /* Rien à trier si tableau nul ou avec moins de 2 éléments */

	max = get_max(array, size); /* Trouver la plus grande valeur pour connaître le nombre de chiffres */
	for (exp = 1; max / exp > 0; exp *= 10)
	{
		counting_sort_radix(array, size, exp); /* Tri par le chiffre correspondant à exp */
		print_array(array, size); /* Affichage après chaque étape pour visualiser la progression */
	}
}
