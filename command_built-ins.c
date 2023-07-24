#include "main.h"

/**
 * custom_env - Prints the environment
 *
 * Description: This function loops through the global
 * environ array and prints each string followed by a
 * newline.
 *
 * Return: 0 on success
 */

int custom_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, custom_strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}

	return (0);
}

/**
 * custom_cd - Changes to a new directory
 * @args: Argument array passed to function
 * @line_num: Command line number
 *
 * Description: This function handles changing
 * directories. It updates PWD and OLDPWD env
 * vars. Handles NULL, ~ and - args.
 *
 * Return: 0 on success, 1 on failure
 */

int custom_cd(char **args, int line_num)
{
	char *new_dir, *old_dir, cwd[1024];
	char *cd_err = cd_error(args);

	if (args[1] == NULL || custom_strcmp(args[1], "~") == 0)
		new_dir = custom_getenv("HOME");
	else if (custom_strcmp(args[1], "-") == 0)
		new_dir = custom_getenv("OLDPWD");
	else
		new_dir = args[1];
	if (new_dir == NULL)
	{
		perror("Directory not found");
		return (1);
	}
	old_dir = custom_getenv("PWD");
	if (custom_setenv("OLDPWD", old_dir, 1) != 0)
	{
		perror("Could not set OLDPWD environment variable");
		return (1);
	}
	if (chdir(new_dir) != 0)
	{
		print_error(args[0], cd_err, line_num);
		free(cd_err);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Could not get current directory");
		free(cd_err);
		return (1);
	}
	if (custom_setenv("PWD", cwd, 1) != 0)
	{
		perror("Could not set PWD environment variable");
		free(cd_err);
		return (1);
	}
	free(cd_err);
	return (0);
}

/**
 * custom_setenv - Sets an environment variable
 * @name: Name of the environment variable
 * @value: Value to set the variable to
 * @overwrite: Overwrite if variable exists
 *
 * Description: This function creates a new environment
 * variable string, and sets it using putenv().
 *
 * Return: 0 on success, 1 on failure
 */

int custom_setenv(const char *name, const char *value, int overwrite)
{
	int idx_i, x;
	int len;
	char *env;

	if (name == NULL || value == NULL)
	{
		perror("Invalid arguments");
		return (1);
	}
	len = custom_strlen(name) + custom_strlen(value) + 2;
	env = malloc(len);
	if (env == NULL)
	{
		perror("Memory allocation failed");
		return (1);
	}
	for (idx_i = 0; name[idx_i] != '\0'; idx_i++)
	{
		env[idx_i] = name[idx_i];
	}
	env[idx_i] = '=';

	for (x = 0; value[x] != '\0'; x++)
	{
		env[idx_i + x + 1] = value[x];
	}
	env[idx_i + x + 1] = '\0';
	if (overwrite == 0 && custom_getenv(name) != NULL)
	{
		free(env);
		return (0);
	}
	if (putenv(env) != 0)
	{
		perror("Setting environment variable failed");
		free(env);
		return (1);
	}
	free(env);
	return (0);
}

/**
 * custom_unsetenv - Removes an environment variable
 * @args: Argument array
 *
 * Description: This function loops through environ
 * and removes the variable name provided in args[1]
 * by shifting the remaining variables down.
 *
 * Return: 0 on success, 1 on failure
*/

int custom_unsetenv(char **args)
{
	int i, x;
	char *name = args[1];
	int len = custom_strlen(name);

	if (args[1] == NULL || args[2] != NULL)
	{
		perror("Invalid argument");
		return (1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (custom_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			for (x = i; environ[x] != NULL; x++)
			{
				environ[x] = environ[x + 1];
			}
			break;
		}
	}

	return (0);
}

/**
 * custom_exit - Exits the shell with a status
 * @args: Arguments array
 *
 * Description: Parses the exit status from args[1],
 * checks validity, frees arguments and exits.
 * Handles optional '+' prefix.
 *
 * Return: 0 on success, -1 on failure
*/

int custom_exit(char **args)
{
	unsigned int exit_status = 0;
	unsigned int max = 1 << (sizeof(int) * 8 - 1);
	int i = 0, len = 10;

	if (args[1] != NULL)
	{
		if (args[1][0] == '+')
		{
			i = 1;
			len++;
		}

		if (args[1][i] != '\0')
		{
			while (args[1][i] != '\0')
			{
				if (i <= len && args[1][i] >= '0' && args[1][i] <= '9')
				{
					exit_status = (exit_status * 10) + (args[1][i] - '0');
				}
				else
				{
					printf("Invalid exit status.\n");
					return (-1);
				}
				i++;
			}

			if (exit_status > max - 1)
			{
				printf("Invalid exit status.\n");
				return (-1);
			}
		}
	}
	custom_freeargs(args);
	exit(exit_status);
}
