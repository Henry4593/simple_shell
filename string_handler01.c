#include "main.h"

/**
 * custom_strcat - Concatenates two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 *
 * Description: This function appends the source string
 * to the destination string by copying characters and
 * adding a terminating null byte.
 *
 * Return: Pointer to resulting concatenated string dest
 */

char *custom_strcat(char *dest, const char *src)
{
	char *p = dest;

	while (*p)
	{
		p++;
	}
	if (src)
	{
		while (*src)
		{
			*p++ = *src++;
		}
	}
	*p = '\0';

	return (dest);
}

/**
 * custom_strcpy - Copies a string
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 *
 * Description: This function copies the source string
 * into the destination by copying characters until the
 * null terminator is reached. It handles trailing spaces.
 *
 * Return: Pointer to destination string
 */

char *custom_strcpy(char *dest, const char *src)
{
	char *p;

	while (*src == ' ')
	{
		src++;
	}

	p = dest;
	while (*src)
	{
		*p++ = *src++;
	}

	while (p > dest && *(p - 1) == ' ')
	{
		p--;
	}

	*p = '\0';

	return (dest);
}
