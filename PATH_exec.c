#include "main.h"

/**
 * execute_with_path - Executes command by searching PATH
 * @args: Array of command arguments
 *
 * Description: Loops through PATH linked list, appends
 * command to each path to build full path, and executes
 * if file exists.
 *
 * Return: 0 on success, -1 on failure
 */

int execute_with_path(char **args)
{
	path_t *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			execve(fullpath, args, NULL);
		}
		temp = temp->next;
	}
	return (-1);

}

/**
 * check_path - Checks if command is in PATH
 * @args: Command argument array
 *
 * Description: Loops through PATH and checks if
 * command exists in any path directory.
 *
 * Return: 1 if found, -1 otherwise
 */

int check_path(char **args)
{
	path_t *temp = link_path();
	char fullpath[1024];

	while (temp != NULL)
	{
		sprintf(fullpath, "%s/%s", temp->dir, args[0]);
		if (access(fullpath, F_OK) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (-1);
}

/**
 * link_path - Links PATH directories into list
 *
 * Description: Tokenizes PATH into directories
 * and links each one into a linked list.
 *
 * Return: Pointer to head of linked list
 */

path_t *link_path(void)
{
	char *dir;
	char *Path;
	char *Path_dup;
	path_t *head;
	path_t *current_node = (path_t *)malloc(sizeof(path_t));

	head = current_node;


	Path = custom_getenv("PATH");
	Path_dup = custom_strdup(Path);
	dir = custom_str_tok(Path_dup, ":");
	current_node->dir = custom_strdup(dir);

	while (dir != NULL)
	{
		dir = custom_str_tok(NULL, ":");
		if (dir != NULL)
		{
			current_node->next = (path_t *)malloc(sizeof(path_t));
			current_node = current_node->next;
			current_node->dir = custom_strdup(dir);
		}
	}
	current_node->next = NULL;

	return (head);

}
