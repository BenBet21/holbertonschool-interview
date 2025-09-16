#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * print_tableau - Affiche les éléments d'un tableau d'entiers
 * @tableau: Le tableau à afficher
 * @taille: Le nombre d'éléments dans le tableau
 *
 * Affiche les éléments séparés par une virgule et un espace.
 */
void print_array(const int *array, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        if (i > 0)
            printf(", ");
        printf("%d", array[i]);
    }
    printf("\n");
}

/**
 * trouver_maximum - Cherche la plus grande valeur dans un tableau
 * @tableau: Le tableau de nombres dans lequel on va chercher
 * @taille: Le nombre d'éléments présents dans le tableau
 *
 * Cette fonction parcourt chaque case du tableau et garde en mémoire
 * la plus grande valeur trouvée.
 *
 * Return: La valeur la plus élevée contenue dans le tableau
 */
static int trouver_maximum(int *tableau, size_t taille)
{
    size_t indice;
    int maximum = tableau[0];

    for (indice = 1; indice < taille; indice++)
    {
        if (tableau[indice] > maximum)
            maximum = tableau[indice];
    }

    return (maximum);
}

/**
 * tri_comptage_chiffre - Trie le tableau en fonction d’un chiffre particulier
 * @tableau: Le tableau de nombres à trier
 * @taille: Le nombre d’éléments dans le tableau
 * @exposant: L'exposant 10^n qui permet d’isoler le chiffre considéré
 *
 * Cette fonction est une variante du tri par comptage.
 * Elle trie uniquement en fonction d’un chiffre du nombre (unités, dizaines, centaines...).
 * Par exemple : avec exposant = 10, on trie par rapport au chiffre des dizaines.
 */
static void tri_comptage_chiffre(int *tableau, size_t taille, int exposant)
{
    int *temporaire, compteur[10] = {0};
    size_t indice;

    // Allocation mémoire pour le tableau trié temporairement
    temporaire = malloc(sizeof(int) * taille);
    if (!temporaire)
        return;

    // Comptage du nombre d’occurrences de chaque chiffre
    for (indice = 0; indice < taille; indice++)
        compteur[(tableau[indice] / exposant) % 10]++;

    // Transformation en "tableau cumulatif" pour connaître les positions finales
    for (indice = 1; indice < 10; indice++)
        compteur[indice] += compteur[indice - 1];

    // Placement des éléments dans le tableau temporaire, en partant de la fin
    for (indice = taille; indice > 0; indice--)
    {
        temporaire[compteur[(tableau[indice - 1] / exposant) % 10] - 1] = tableau[indice - 1];
        compteur[(tableau[indice - 1] / exposant) % 10]--;
    }

    // Copie du tableau trié dans le tableau d’origine
    for (indice = 0; indice < taille; indice++)
        tableau[indice] = temporaire[indice];

    // Libération de la mémoire utilisée par le tableau temporaire
    free(temporaire);
}

/**
 * tri_radix - Trie un tableau d’entiers avec le tri par base (Radix Sort)
 * @tableau: Le tableau de nombres que l’on veut trier
 * @taille: Le nombre d’éléments dans le tableau
 *
 * Le tri radix trie les nombres chiffre par chiffre,
 * en commençant par les unités, puis les dizaines, puis les centaines, etc.
 */
void tri_radix(int *tableau, size_t taille)
{
    int maximum, exposant;

    if (!tableau || taille < 2)
        return;

    // On identifie le plus grand nombre pour savoir combien de chiffres traiter
    maximum = trouver_maximum(tableau, taille);

    // On trie successivement selon chaque chiffre (unités, dizaines, centaines…)
    for (exposant = 1; maximum / exposant > 0; exposant *= 10)
    {
        tri_comptage_chiffre(tableau, taille, exposant);
    print_array(tableau, taille); // Affiche le tableau à chaque étape
    }
}
