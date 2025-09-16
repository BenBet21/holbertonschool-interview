#include "holberton.h"

/**
 * comparaison_sauvage - Compare deux chaînes de caractères en tenant compte du joker '*'
 * @chaine1: Première chaîne de caractères
 * @chaine2: Deuxième chaîne de caractères (peut contenir le caractère spécial '*')
 * 
 * Retourne: 
 *  1 si les deux chaînes peuvent être considérées comme identiques (en tenant compte du '*')
 *  0 sinon.
 *
 * Explication pédagogique :
 * Le caractère '*' est utilisé comme un "joker". 
 * - Il peut correspondre à une chaîne vide (rien). 
 * - Il peut aussi correspondre à une ou plusieurs lettres de la première chaîne.
 * 
 * Cette fonction explore donc plusieurs possibilités lorsqu’elle rencontre '*', 
 * afin de vérifier toutes les correspondances possibles entre les deux chaînes.
 */

int comparaison_sauvage(char *chaine1, char *chaine2)
{
	if (*chaine1 == '\0' && *chaine2 == '\0')
		return (1);

	/* Si on rencontre un '*', plusieurs cas possibles */
	if (*chaine2 == '*')
	{
		/* Cas 1 : si on a deux '*' consécutifs, on ignore le premier */
		if (*(chaine2 + 1) == '*')
			return (comparaison_sauvage(chaine1, chaine2 + 1));

		/* Cas 2 : le '*' correspond à une chaîne vide */
		if (comparaison_sauvage(chaine1, chaine2 + 1))
			return (1);

		/* Cas 3 : le '*' correspond à au moins un caractère de chaine1 */
		if (*chaine1 && comparaison_sauvage(chaine1 + 1, chaine2))
			return (1);

		/* Si aucune correspondance trouvée */
		return (0);
	}

	/* Vérification caractère par caractère quand pas de '*' */
	if (*chaine1 == *chaine2)
		return (comparaison_sauvage(chaine1 + 1, chaine2 + 1));

	return (0);
}

