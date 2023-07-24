#include "main.h"

/**
 * print_error - Prints error message to stderr
 * @cmd: Command causing error
 * @msg: Error message
 * @line_num: Line number of command
 *
 * Description: Prints formatted error message containing
 * shell name, line number, command and message.
 *
 * Return: None
 */

void print_error(const char *cmd, const char *msg, int line_num)
{
	const char *shell_name = "hsh";
	const char *separator = ": ";
	char line_number_str[16];
	unsigned long int idx_i = 0;
	int x, n = line_num;
	size_t shell_name_len = custom_strlen(shell_name);
	size_t separator_len = custom_strlen(separator);

	write(STDERR_FILENO, shell_name, shell_name_len);
	write(STDERR_FILENO, separator, separator_len);

	if (n == 0)
	{
		line_number_str[idx_i++] = '0';
	}
	else
	{
		while (n > 0 && idx_i < sizeof(line_number_str) - 1)
		{
			line_number_str[idx_i++] = '0' + (n % 10);
			n /= 10;
		}
	}
	for (x = idx_i - 1; x >= 0; x--)
	{
		write(STDERR_FILENO, &line_number_str[x], 1);
	}

	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, cmd, custom_strlen(cmd));
	write(STDERR_FILENO, separator, separator_len);
	write(STDERR_FILENO, msg, custom_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * cd_error - Creates CD error message
 * @args: Argument array
 *
 * Description: Concatenates an error message
 * for a failed cd command using the argument strings.
 *
 * Return: Pointer to the error string
 */

char *cd_error(char **args)
{
	char *error_message = (char *)malloc(100 * sizeof(char));

	if (error_message == NULL)
	{
		return (NULL);
	}

	custom_strcpy(error_message, "can't ");
	custom_strcat(error_message, " ");
	custom_strcat(error_message, args[0]);
	custom_strcat(error_message, " to ");
	custom_strcat(error_message, args[1]);

	return (error_message);
}
