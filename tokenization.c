#include "main.h"

/**
 * custom_str_tok - Tokenize string with delimiters
 * @command: The string to tokenize
 * @delimiter: The delimiter characters
 *
 * Description: This function breaks the string into tokens
 * separated by the delimiter characters. It maintains state
 * to continue tokenizing on subsequent calls.
 *
 * Return: Pointer to the current token, NULL if no tokens left
 */

char *custom_str_tok(char *command, const char *delimiter)
{
	static char *last_token;
	char *current_token;

	if (command != NULL)
		last_token = command;

	if (last_token == NULL || *last_token == '\0')
		return (NULL);

	current_token = last_token;
	while (*current_token != '\0' && custom_strchr(delimiter,
				*current_token) != NULL)
		current_token++;

	if (*current_token == '\0')
	{
		last_token = NULL;
		return (NULL);
	}

	last_token = current_token;
	while (*last_token != '\0' && custom_strchr(delimiter, *last_token) == NULL)
		last_token++;

	if (*last_token != '\0')
	{
		*last_token = '\0';
		last_token++;
	}

	return (current_token);
}

/**
 * tokenify - Tokenize a command string into arguments
 * @command: The command string to tokenize
 * @args: Array to store the tokenized arguments
 *
 * Description: This function breaks down the command
 * string into space separated tokens and stores them
 * in the args array to be used as arguments.
 *
 * Return: The number of tokens extracted
 */

int tokenify(char *command, char **args)
{
	int idx_token = 0;
	char *token = custom_str_tok(command, " \n\t\r\a");
	char *trimmed_token;

	while (token != NULL && idx_token < MAXARGS - 1)
	{
		trimmed_token = token;
		while (*trimmed_token == ' ')
		{
			trimmed_token++;
		}

		if (trimmed_token[0] == '#')
		{
			break;
		}

		if (*trimmed_token != '\0')
		{
			args[idx_token++] = trimmed_token;
		}

		token = custom_str_tok(NULL, " \n\t\r\a");
	}
	return (idx_token);
}
