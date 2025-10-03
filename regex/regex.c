#include "regex.h"

/**
 * regex_match - Checks if a pattern matches a string
 * @str: The string to scan
 * @pattern: The regular expression pattern
 *
 * Return: 1 if pattern matches, 0 otherwise
 */
int regex_match(char const *str, char const *pattern)
{
	/* Cas de base : pattern vide */
	if (*pattern == '\0')
		return (*str == '\0');

	/* Vérifie si le prochain caractère est '*' */
	if (*(pattern + 1) == '*')
	{
		/* Cas X* : on peut ignorer le pattern X* (zéro occurrence) */
		if (regex_match(str, pattern + 2))
			return (1);

		/* Ou utiliser X* si le caractère actuel correspond */
		if ((*str != '\0') && (*str == *pattern || *pattern == '.'))
			return (regex_match(str + 1, pattern));

		return (0);
	}

	/* Cas normal : pas de '*' après le caractère actuel */
	if ((*str != '\0') && (*str == *pattern || *pattern == '.'))
		return (regex_match(str + 1, pattern + 1));

	return (0);
}
