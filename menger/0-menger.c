#include "menger.h"
#include <stdio.h>
#include <math.h>

/**
 * is_hole - Détermine si une position donnée doit être un "trou"
 *           dans l'éponge de Menger.
 *
 * Principe :
 * Une case est un trou si, à n'importe quel niveau de subdivision,
 * elle se retrouve au centre d'un carré 3x3.
 *
 * @i: Position de la ligne (row)
 * @j: Position de la colonne (column)
 *
 * Return:
 * 1 si la position correspond à un trou
 * 0 sinon (la position doit être remplie avec '#')
 */
int is_hole(int i, int j)
{
	/*
	 * On remonte récursivement (via une boucle)
	 * dans les niveaux de subdivision.
	 *
	 * Tant que l'une des coordonnées est > 0,
	 * on continue à vérifier les divisions par 3.
	 */
	while (i > 0 || j > 0)
	{
		/*
		 * Si, à ce niveau, i et j sont tous les deux
		 * au centre (reste = 1) d'un bloc 3x3,
		 * alors cette case est un trou.
		 */
		if (i % 3 == 1 && j % 3 == 1)
			return (1);

		/*
		 * On passe au niveau supérieur en divisant
		 * les coordonnées par 3.
		 */
		i /= 3;
		j /= 3;
	}

	/*
	 * Si aucun centre n'a été détecté,
	 * ce n'est pas un trou.
	 */
	return (0);
}

/**
 * menger - Dessine une éponge de Menger en 2D
 *
 * @level: Niveau de l'éponge de Menger
 *
 * Description :
 * - Le niveau détermine la taille de la grille : 3^level
 * - Chaque position est testée pour savoir si elle est
 *   un trou ou non.
 * - Les trous sont affichés avec un espace ' '
 * - Les parties pleines sont affichées avec '#'
 */
void menger(int level)
{
	int size;
	int i;
	int j;

	/*
	 * Si le niveau est négatif, on ne dessine rien.
	 */
	if (level < 0)
		return;

	/*
	 * Calcul de la taille totale de la grille :
	 * taille = 3 puissance level
	 */
	size = pow(3, level);

	/*
	 * Parcours ligne par ligne
	 */
	for (i = 0; i < size; i++)
	{
		/*
		 * Parcours colonne par colonne
		 */
		for (j = 0; j < size; j++)
		{
			/*
			 * On vérifie si la position (i, j)
			 * correspond à un trou
			 */
			if (is_hole(i, j))
				printf(" ");
			else
				printf("#");
		}

		/*
		 * Retour à la ligne après chaque ligne
		 */
		printf("\n");
	}
}
