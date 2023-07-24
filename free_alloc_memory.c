#include "main.h"

/**
 * custom_freeargs - Frees a 2D array of arguments
 * @args: The array of arguments to free
 *
 * Description: Loops through and frees each string
 * in the argument array.
 *
 * Return: void
 */

void  custom_freeargs(char **args)
{
	int index;
	int len = 0;

	while (args[len] != NULL)
		len++;

	for (index = 0; index < len; index++)
	{
		free(args[index]);
	}
}

/**
 * custom_free_path - Frees a linked list of path nodes
 * @path: Pointer to the head of the path list
 *
 * Description: Loops through the linked list and frees
 * each node's directory string and the node itself.
 *
 * Return: void
 */

void custom_free_path(path_t *path)
{
	path_t *temp;

	while (temp != NULL)
	{
		temp = path->next;
		free(path->dir);
		free(path);
		path = temp;
	}
}

/**
 * custom_freeenv - Frees the environ array
 *
 * Description: Loops through and frees each string
 * in the global environ array, then frees the array itself.
 *
 * Return: void
 */

void custom_freeenv(void)
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		free(environ[index]);
	}
	free(environ);
}
