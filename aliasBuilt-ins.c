#include "main.h"

/**
 * check_alias - Checks if an alias exists for a command
 * @neww: The command to check for an alias
 *
 * Description: This function loops through the alias
 * list and compares each alias name to the passed command
 * string. If a match is found, the alias name is returned.
 * If no match, NULL is returned.
 *
 * Return: Pointer to alias name if found, NULL otherwise
 */

char *check_alias(char *neww)
{
	alias_t *temp = get_alias_list();

	while (temp != NULL)
	{
		if (custom_strcmp(neww, temp->new_command) == 0)
		{
			return (temp->new_command);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * execute_alias - Executes a command if alias exists
 * @main: The command name to execute
 * @args: Array of command arguments
 *
 * Description: This function checks if the command is
 * an alias, and if so, executes the command using execve().
 * If execve fails, an error is printed and the program exits.
 *
 * Return: 0 on success, EXIT_FAILURE if execve fails
 */

int execute_alias(char *main, char **args)
{
	if (execve(main, args, environ) == -1)
	{
		fprintf(stderr, "%s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * create_keyvalue_pair - Creates a key-value alias pair
 * @name: The alias declaration string
 * @alias_list: Pointer to alias list head
 * @equals: Pointer to '=' separator in name
 *
 * Description: This function parses the alias declaration
 * string to extract the alias name and command, allocates
 * new strings for them, and adds the pair to the alias list.
 *
 * Return: 0 on success
 */

int create_keyvalue_pair(alias_t **alias_list, char *name, char *equals)
{
	alias_t *alias_list_cpy = *alias_list;
	int idx_i, b = 0, x,  value_length;
	char *main_command, *new_command = malloc((strlen(name) + 1) * sizeof(char));

	while (name[b] != '=')
	{
		new_command[b] = name[b];
		b++;
	}

	*equals = '\0';
	equals = equals + 1;

	printf("now allocating memory for value_command equals = %s\n", equals);
	value_length = strlen(equals) - strspn(equals, "'\"");
	main_command = malloc(sizeof(char) * (value_length + 1));

	printf("now entering initialization loop\n");
	for (idx_i = 0, x = 0; equals[idx_i] != '\0'; idx_i++)
	{
		if (equals[idx_i] != '\'' && equals[idx_i] != '"')
		{
			main_command[x] = equals[idx_i];
			x++;
		}
	}
	main_command[x] = '\0';

	printf("before add name = %s and value = %s\n", new_command, main_command);
	*alias_list = add_alias(&alias_list_cpy, new_command, main_command);

	return (0);
}

/**
 * add_alias - Adds a new alias to the alias list
 * @head: Pointer to the head of the alias list
 * @new: The new alias name
 * @main: The existing command for the alias
 *
 * Description: This function allocates a new node for the
 * alias pair and adds it to the alias list. If the alias
 * name already exists, its command is replaced with the
 * new one.
 *
 * Return: Pointer to the head of the updated list
 */

alias_t *add_alias(alias_t **head, char *new, char *main)
{
	alias_t *new_node = NULL;
	alias_t *temp;

	new_node->main_command = malloc(sizeof(char) * 50);
	new_node->new_command = malloc(sizeof(char) * 50);

	new_node->main_command = custom_strdup(main);
	new_node->new_command = custom_strdup(new);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			if (strcmp(new, temp->new_command) == 0)
			{
				free(temp->main_command);
				temp->main_command = custom_strdup(main);
				free(new_node->main_command);
				free(new_node->new_command);
				return (*head);
			}
			temp = temp->next;
		}
		temp->next = new_node;
	}
	printf("added alias to list successfully\n");

	while (temp != NULL)
	{
		printf("alias is %s='%s'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	return (*head);
}

/**
 * printOut_alias_list - Prints the alias list
 * @head: Pointer to head of alias list
 *
 * Description: This function loops through the alias
 * list and prints each alias name and its corresponding
 * command.
 *
 * Return: 0 on success
 */

int printOut_alias_list(alias_t *head)
{
	alias_t *temp = head;

	while (temp != NULL)
	{
		printf("alias %s=\'%s\'\n", temp->new_command, temp->main_command);
		temp = temp->next;
	}
	printf("print list successfully\n");

	return (0);
}
