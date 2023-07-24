#include "main.h"

/**
 * execute - Executes a command
 * @command: The command string
 * @line_num: Line number of command
 *
 * Description: Parses command into arguments,
 * checks if built-in, finds full path if not,
 * forks, runs parent/child processes, waits for child.
 *
 * Return: Exit status of command
 */

int execute(char *command, int line_num)
{
	char *args[MAXARGS];
	char command_path[MAX_PATH_LENGTH];
	pid_t pid;
	int idx, EXT_stat = 0;

	idx = tokenify(command, args);
	args[idx] = NULL;

	if (built_ins(args, line_num) || built_ins2(args, line_num))
		return (0);
	if (access(args[0], X_OK) == -1)
	{
		custom_strcpy(command_path, "/bin/");
		custom_strcat(command_path, args[0]);
		if (access(command_path, X_OK) == -1)
		{
			print_error(args[0], "not found", line_num);
			return (0);
		}
	}

	pid = fork();

	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid != 0)
		EXT_stat = run_parent();

	if (pid == 0 && args[0][0] != '\0')
	{
		EXT_stat = run_child(args);
	}

	return (EXT_stat);
}

/**
 * run_child - Child process executes command
 * @args: Argument array
 *
 * Description: Handles executing command for child.
 * Checks for full path, searches PATH if not,
 * executes with execve or errors.
 *
 * Return: 0 on success
 */

int run_child(char **args)
{
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (check_path(args) == 1)
	{
		execute_with_path(args);
	}
	else
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * run_parent - Parent process waits for child
 *
 * Description: Parent process calls EXT_stat()
 * to wait for child process to finish.
 *
 * Return: Exit status of child
 */

int run_parent(void)
{
	EXT_stat();
	return (0);
}

/**
 * EXT_stat - Gets exit status of child process
 *
 * Description: Calls wait() to wait for child
 * process completion. Parses status and returns
 * exit status.
 *
 * Return: Exit status of child
 */

int EXT_stat(void)
{
	int status;
	static int exit_status;

	wait(&status);

	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
