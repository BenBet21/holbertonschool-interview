#include "holberton.h"

/**
 * wildcmp - Compare deux chaînes de caractères en prenant en compte
 * le caractère générique '*' (joker).
 * @s1: Première chaîne de caractères à comparer.
 * @s2: Deuxième chaîne de caractères à comparer (peut contenir '*').
 *
 * Description:
 * Cette fonction compare deux chaînes et considère que le caractère '*'
 * de s2 peut représenter n'importe quelle suite (même vide) de caractères.
 *
 * Exemple:
 * - s1 = "bonjour", s2 = "b*jour"  -> retourne 1 (car * remplace "on")
 * - s1 = "chat", s2 = "ch*t"       -> retourne 1 (car * remplace "a")
 * - s1 = "chat", s2 = "c*t"        -> retourne 0 (manque 'h')
 *
 * Return: 1 si les chaînes sont considérées identiques,
 * 0 sinon.
 */
int wildcmp(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);

	/* Si s2 contient un '*', plusieurs cas sont possibles */
	if (*s2 == '*')
	{
		/* Cas 1: Si plusieurs '*' se suivent, on les ignore */
		if (*(s2 + 1) == '*')
			return (wildcmp(s1, s2 + 1));

		/* Cas 2: Le '*' remplace zéro caractère -> on avance dans s2 */
		if (wildcmp(s1, s2 + 1))
			return (1);

		/* Cas 3: Le '*' remplace au moins un caractère -> on avance dans s1 */
		if (*s1 && wildcmp(s1 + 1, s2))
			return (1);

		return (0);
	}

	/* Si les caractères actuels sont identiques, on continue la comparaison */
	if (*s1 == *s2)
		return (wildcmp(s1 + 1, s2 + 1));

	/* Sinon, les chaînes ne correspondent pas */
	return (0);
}
