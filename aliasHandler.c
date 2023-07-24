#include "main.h"

/**
 * custom_alias - Handles custom alias commands
 * @args: Array of command arguments
 *
 * Description: This function checks if the command
 * arguments contain an alias definition, print request,
 * or alias execution. It performs the appropriate
 * action for each case.
 *
 * Return: 0 on success
 */

int custom_alias(char **args)
{
	int idx_i = 1;
	alias_t *alias_list_cpy = get_alias_list();
	char *equals;

	if (args[idx_i] == NULL)
	{
		if (alias_list_cpy == NULL)
			printf("NULL\n");
		else
		{
			printf("wants to enter print alias list\n");
			printOut_alias_list(alias_list_cpy);
		}
		return (0);
	}
	for (idx_i = 1; args[idx_i] != NULL; idx_i++)
	{
		equals = strchr(args[idx_i], '=');
		alias_list_cpy = get_alias_list();
		if (equals == NULL)
		{
			while (alias_list_cpy != NULL)
			{
				if (strcmp(args[idx_i], alias_list_cpy->main_command) == 0)
				{
					printOut_alias_list(alias_list_cpy);
					break;
				}
				alias_list_cpy = alias_list_cpy->next;
			}
		}
		else
		{
			printf("create keyvalue_pair function args = %s \n", args[idx_i]);
			create_keyvalue_pair(&alias_list_cpy, args[idx_i], equals);
		}
	}
	return (0);
}

/**
 * get_alias_list - Gets the alias list
 *
 * Description: This function simply returns the global
 * alias list pointer. It can be used to access the alias
 * list from other parts of the program.
 *
 * Return: Pointer to the alias list
 */

alias_t *get_alias_list(void)
{
	alias_t *alias_list = NULL;

	return (alias_list);
}
