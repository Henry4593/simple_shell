#include "main.h"

/**
 * get_dir - Gets the current working directory
 *
 * Description: This function returns a pointer to a
 * string containing the path of the current working
 * directory. It first allocates memory for the path
 * string, then calls getcwd() to populate the string,
 * and returns the pointer.
 *
 * If either the memory allocation or getcwd() fails,
 * NULL is returned and errno is set appropriately.
 *
 * Return: Pointer to the cwd string, NULL on failure
 */

char *get_dir()
{
	char *cwd = malloc(sizeof(char) * 1024);

	if (cwd == NULL)
	{
		perror("malloc error");
		return (NULL);
	}

	if (getcwd(cwd, 1024) != NULL)
	{
		return (cwd);
	}
	else
	{
		perror("getcwd error");
		free(cwd);
		return (NULL);
	}
}

/**
 * custom_getenv - Gets the value of an environment variable
 * @name: The name of the environment variable to get
 *
 * Description: This function searches the environment
 * list for a variable matching the given name. If found,
 * it returns a pointer to the value of that variable.
 * If not found, NULL is returned.
 *
 * Return: Pointer to the variable value, or NULL if not found
 */

char *custom_getenv(const char *name)
{
	int idx_env = 0;
	char *environ_temp;
	char *equals;

	while (environ[idx_env] != NULL)
	{
		environ_temp = environ[idx_env];
		equals = custom_strchr(environ_temp, '=');

		*equals = '\0';
		if (custom_strcmp(environ_temp, name) == 0)
		{
			*equals = '=';
			return (environ[idx_env] + custom_strlen(name) + 1);
		}
		*equals = '=';
		idx_env++;
	}
	return (NULL);
}

/**
 * custom_getline - Reads a line from a file descriptor
 * @buffer: Address of pointer to buffer to store line
 * @bufsize: Address of buffer size variable
 * @fd: File descriptor to read from
 *
 * Description: This function reads bytes from the file
 * descriptor one at a time into a buffer until a newline
 * is encountered or EOF is reached. The buffer is grown
 * dynamically if needed.
 *
 * Return: Number of bytes read on success, -1 on failure
*/

ssize_t custom_getline(char **buffer, size_t *bufsize, int fd)
{
	static size_t line_buffer_size = 1024;
	ssize_t read_bytes;
	size_t len = 0;
	*bufsize = line_buffer_size;
	*buffer = malloc(*bufsize * sizeof(char));

	if (*buffer == NULL)
	{
		not_buff();
	}

	while ((read_bytes = read(fd, *buffer + len, 1)) > 0)
	{
		if ((*buffer)[len] == '\n')
		{
			(*buffer)[len] = '\0';
			return (len);
		}
		len++;

		if (len >= *bufsize)
		{
			*bufsize *= 2;
			*buffer = realloc(*buffer, *bufsize * sizeof(char));
			if (!*buffer)
				not_buff();
			free(*buffer);
			return (-1);
		}
	}
	if (read_bytes == -1)
	{
		free(*buffer);
		perror("read");
		exit(EXIT_FAILURE);
	}
	free(*buffer);
	return (-1);
}

/**
 * not_buff - Prints error and exits if buffer failed
 *
 * Description: This function prints an error message
 * using perror() and exits the program with failure
 * if buffer allocation failed in custom_getline().
 *
 * Return: None (exits program)
*/

void not_buff(void)
{
	perror("custom_getline");
	exit(EXIT_FAILURE);
}
