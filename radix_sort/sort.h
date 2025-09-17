#ifndef SORT_H
#define SORT_H

#include <stddef.h>

/**
 * print_array - Affiche le contenu d'un tableau d'entiers
 * @array: pointeur vers le tableau à afficher
 * @size: nombre d'éléments dans le tableau
 *
 * Cette fonction parcourt le tableau et affiche chaque entier, ce qui
 * permet de visualiser l'état du tableau (utile pour le débogage ou
 * pour comprendre l'évolution d'un algorithme de tri).
 */
void print_array(const int *array, size_t size);

/**
 * radix_sort - Trie un tableau d'entiers en utilisant l'algorithme Radix Sort
 * @array: pointeur vers le tableau à trier
 * @size: nombre d'éléments dans le tableau
 *
 * Le tri par base (Radix Sort) est un algorithme efficace pour trier
 * des entiers. Il trie les nombres en fonction de leurs chiffres,
 * en commençant par le chiffre le moins significatif jusqu'au plus
 * significatif. Ce tri est stable et non comparatif.
 */
void radix_sort(int *array, size_t size);

#endif
