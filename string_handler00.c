#include "main.h"

/**
 * custom_strlen - Gets the length of a string
 * @s: The string to get the length of
 *
 * Description: This function returns the length of
 * the string s. It counts the number of characters
 * until the null terminating character is reached.
 *
 * Return: The length of the string
 */

int custom_strlen(const char *s)
{
	int length = 0;

	if (s == NULL)
		return (-1);
	while (s[length] != '\0')
		length++;
	return (length);
}

/**
 * custom_strcmp - Compares two strings
 * @s1: The first string to compare
 * @s2: The second string to compare
 *
 * Description: This function compares two strings character
 * by character. It returns an integer indicating if s1 is
 * less than, equal to or greater than s2.
 *
 * Return: < 0 if s1 is less than s2, 0 if s1 equals s2,
 * > 0 if s1 is greater than s2.
 */

int custom_strcmp(const char *s1, const char *s2)
{
	const char *p1 = s1;
	const char *p2 = s2;
	int idx_str = 0;

	if (p1 == NULL && p2 == NULL)
		return (0);
	else if (p1 == NULL)
		return (-1);
	else if (p2 == NULL)
		return (1);

	while (*(p1 + idx_str) != '\0' && *(p2 + idx_str) != '\0' &&
			p1[idx_str] == p2[idx_str])
	{
		idx_str++;
	}
	return (p1[idx_str] - p2[idx_str]);
}

/**
 * custom_strchr - Finds character in string
 * @s: The string to search
 * @c: The character to find
 *
 * Description: This function finds the first
 * occurrence of character c in string s.
 *
 * Return: Pointer to location of c in s, or NULL if not found.
 */

char *custom_strchr(const char *s, const char c)
{
	const char *ptr_s = s;
	const char *ptr_c = &c;
	int idx_str;

	for (idx_str = 0; *(ptr_s + idx_str) != '\0'; idx_str++)

		if (*(ptr_s + idx_str) == *ptr_c)
		{
			return ((char *)(s + idx_str));
		}

	return (0);
}

/**
 * custom_strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Description: This function allocates memory for a
 * new string, copies the contents of str into it,
 * and returns the pointer.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */

char *custom_strdup(const char *str)
{
	int idx, len = 0;
	char *r_value;

	if (str == NULL)
		return (NULL);

	for (; str[len] != '\0'; len++)
		;

	r_value = malloc(sizeof(char) * (len + 1));
	if (r_value == NULL)
		return (NULL);

	for (idx = 0; idx <= len; idx++)
		r_value[idx] = str[idx];

	return (r_value);
}

/**
 * custom_strncmp - Compare two strings up to n characters
 * @s1: First string to compare
 * @s2: Second string to compare
 * @n: Maximum number of characters to compare
 *
 * Description: This function compares up to n characters
 * of two strings s1 and s2. It compares characters
 * until it finds a difference or reaches n.
 *
 * Return: < 0 if s1 is less than s2, 0 if equal, > 0 if s1 is greater.
 */

int custom_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char p1, p2;
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	for (i = 0; i < n; i++)
	{
		p1 = (unsigned char)s1[i];
		p2 = (unsigned char)s2[i];

		if (p1 != p2)
			return (p1 - p2);
		if (p1 == '\0')
			break;
	}

	return (0);
}
