#include "palindrome.h"

/**
 * is_palindrome - Vérifie si un nombre entier non signé est un palindrome
 * @n: Le nombre à vérifier
 *
 * Description: Cette fonction inverse les chiffres du nombre et compare
 * le résultat avec le nombre original. Un palindrome se lit pareil
 * dans les deux sens (ex: 121, 1001, 9).
 *
 * Return: 1 si n est un palindrome, 0 sinon
 */
int is_palindrome(unsigned long n)
{
	unsigned long original;   /* Sauvegarde du nombre original */
	unsigned long reversed;   /* Le nombre inversé qu'on va construire */
	unsigned long temp;       /* Variable temporaire pour les calculs */

	/* Cas spéciaux : les nombres à un chiffre sont toujours des palindromes */
	if (n < 10)
		return (1);

	/* Sauvegarder le nombre original pour la comparaison finale */
	original = n;
	reversed = 0;
	temp = n;

	/* Boucle pour inverser les chiffres du nombre */
	while (temp > 0)
	{
		/* Extraire le dernier chiffre de temp */
		unsigned long last_digit = temp % 10;
		
		/* Ajouter ce chiffre à reversed */
		/* On multiplie par 10 pour décaler les chiffres déjà présents */
		reversed = reversed * 10 + last_digit;
		
		/* Enlever le dernier chiffre de temp */
		temp = temp / 10;
	}

	/* Comparer le nombre original avec sa version inversée */
	if (original == reversed)
		return (1);  /* C'est un palindrome */
	else
		return (0);  /* Ce n'est pas un palindrome */
}
