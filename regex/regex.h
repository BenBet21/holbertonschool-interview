#ifndef REGEX_H
#define REGEX_H

/**
 * regex_match - Checks if a pattern matches a string
 * @str: The string to scan
 * @pattern: The regular expression pattern
 *
 * Return: 1 if pattern matches, 0 otherwise
 */
int regex_match(char const *str, char const *pattern);

#endif
