#include "main.h"

/**
 * main - Entry point for the shell program
 * @argc: Number of arguments (unused)
 * @argv: Array of argument strings
 *
 * Description: Runs an interactive or non-interactive
 * command line interpreter shell. Displays prompt,
 * reads input, tokenizes then executes commands.
 *
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	bool is_interactive_mode = isatty(STDIN_FILENO);
	char *shellPrompt = is_interactive_mode ? "custom_shell$: " : "";
	size_t n = 0;
	ssize_t line;
	int line_num = 1;
	char **cmd;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		if (is_interactive_mode)
		{
			write(STDOUT_FILENO, shellPrompt, 16);
			fflush(stdout);
		}
		line = custom_getline(argv, &n, STDIN_FILENO);
		if (line == -1)
		{
			if (feof(stdin))
			{
				exit(EXIT_SUCCESS);
			}
			break;
		}
		if (line == 0 || *argv[0] == '\n')
			continue;
		cmd = argv;
		while (*cmd != NULL)
		{
			execute(*cmd, line_num);
			cmd++;
		}
		custom_freeargs(argv);
		line_num++;
	}
	return (0);
}
