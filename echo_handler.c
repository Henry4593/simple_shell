#include "main.h"

/**
 * custom_itoa - Converts an integer to a string
 * @value: The integer to convert
 *
 * Description: This function allocates a string and
 * fills it with the string representation of
 * the integer value provided.
 *
 * Return: Pointer to the converted string
*/

char *custom_itoa(int value)
{
	int y, len = 0;
	int temp = value;
	char *str = (char *)malloc((len + 1) * sizeof(char));

	while (temp != 0)
	{
		len++;
		temp /= 10;
	}

	if (value == 0)
	{
		len = 1;
	}

	if (str == NULL)
	{
		return (NULL);
	}

	for (y = len - 1; y >= 0; y--)
	{
		str[y] = '0' + (value % 10);
		value /= 10;
	}

	str[len] = '\0';

	return (str);
}

/**
 * custom_echo - Prints arguments to standard output
 * @args: Argument array
 *
 * Description: Prints each argument to stdout, handling
 * special cases like $$ and $?. Replaces env vars.
 *
 * Return: Number of characters printed
 */

int custom_echo(char **args)
{
	int idx, len;
	int printed_chars = 0;

	for (idx = 1; args[idx] != NULL && idx < MAXARGS - 1; idx++)
	{
		if (custom_strcmp(args[idx], "$$") == 0)
		{
			echo_ppid(printed_chars);
		}
		else if (custom_strcmp(args[idx], "$?") == 0)
		{
			echo_exit(printed_chars);
		}
		else if (args[idx][0] == '$')
		{
			echo_env(printed_chars, args, idx);
		}
		else
		{
			len = custom_strlen(args[idx]);
			printed_chars += write(STDOUT_FILENO, args[idx], len);
			printed_chars += len;
		}
		if (args[idx + 1] != NULL)
		{
			printed_chars += write(STDOUT_FILENO, " ", 1);
			printed_chars++;
		}
	}
	return (printed_chars);
}

/**
 * echo_ppid - Prints current PID
 * @printed_chars: Number of chars printed so far
 *
 * Description: Gets and prints the current PID
 * to stdout. Updates printed_chars count.
 *
 * Return: 0 on success
 */

int echo_ppid(int printed_chars)
{
	int len;
	pid_t pid;
	char *pid_str;

			pid = getpid();
			pid_str = custom_itoa(pid);

			if (pid_str != NULL)
			{
				len = custom_strlen(pid_str);

				printed_chars += write(STDOUT_FILENO, pid_str, len);
				free(pid_str);
			}
			return (0);
}

/**
 * echo_exit - Prints exit status
 * @printed_chars: Number of chars printed so far
 *
 * Description: Gets the exit status, converts to string,
 * prints to stdout. Updates printed_chars count.
 *
 * Return: 0 on success
 */

int echo_exit(int printed_chars)
{

	int exit_status = EXT_stat();
	char *exit_status_str = custom_itoa(exit_status);

	if (exit_status_str != NULL)
	{
		int len = custom_strlen(exit_status_str);

		printed_chars += write(STDOUT_FILENO, exit_status_str, len);
		free(exit_status_str);
	}
	return (0);
}

/**
 * echo_env - Prints environment variable
 * @printed_chars: Number of chars printed so far
 * @args: Argument array
 * @i: Current argument index
 *
 * Description: Gets the env var name from args[i],
 * gets value from environ, prints to stdout.
 * Updates printed_chars count.
 *
 * Return: 0 on success
 */

int echo_env(int printed_chars, char **args, int i)
{
	int len;
	char *value;
	char *var_name;

	var_name = args[i] + 1;
	value = custom_getenv(var_name);

	if (value != NULL)
	{
		len = custom_strlen(value);
		printed_chars += write(STDOUT_FILENO, value, len);
		printed_chars += len;
	}
	else
		return (0);
	return (0);
}
