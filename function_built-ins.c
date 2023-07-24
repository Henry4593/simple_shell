#include "main.h"

/**
 * built_ins - Checks and runs builtin commands
 * @args: Array of command arguments
 * @line_num: Line number of command
 *
 * Description: Compares args[0] and executes the
 * corresponding builtin function if match.
 *
 * Return: 1 if builtin, 0 otherwise
 */

int built_ins(char **args, int line_num)
{
	if (args[0] == NULL)
		return (1);

	if (custom_strcmp(args[0], "exit") == 0)
	{
		custom_exit(args);
		exit(2);
	}
	if (custom_strcmp(args[0], "env") == 0)
	{
		custom_env();
		return (1);
	}
	if (custom_strcmp(args[0], "cd") == 0)
	{
		custom_cd(args, line_num);
		return (1);
	}
	if (custom_strcmp(args[0], "setenv") == 0)
	{
		custom_setenv(args[1], args[2], 1);
		return (1);
	}
	if (custom_strcmp(args[0], "unsetenv") == 0)
	{
		custom_unsetenv(args);
		return (1);
	}
	return (0);
}

/**
 * built_ins2 - Checks and runs builtin commands
 * @args: Array of command arguments
 * @line_num: Line number of command (unused)
 *
 * Description: Compares args[0] and executes the
 * corresponding builtin function if match.
 *
 * Return: 1 if builtin, 0 otherwise
*/

int built_ins2(char **args, int line_num __attribute__ ((unused)))
{
	if (custom_strcmp(args[0], "alias") == 0)
	{
		custom_alias(args);
		return (1);
	}
	if (custom_strcmp(args[0], "echo") == 0)
	{
		custom_echo(args);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}

	return (0);
}
