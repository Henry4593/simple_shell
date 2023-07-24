#include "main.h"

/**
 * sigintHandler - Handles SIGINT signal (Ctrl+C)
 * @sig_num: Signal number (unused)
 *
 * Description: This function is called when SIGINT
 * is received. It prints a new line and re-enables
 * the handler to catch the next SIGINT.
 *
 * Return: void
 */

void sigintHandler(int sig_num)
{
	(void)sig_num;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, sigintHandler);
}
