#ifndef MAIN_H
#define MAIN_H

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

/* header file containing systems functions*/
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/** Global environment */
extern char **environ;
extern int exit_status;

/** MACROS **/
#define MAXARGS 128
#define MAX_PATH_LENGTH 256

/**
 * struct alias_t - This is a linked list containing
 * original command name and new name to be substituted.
 *
 * @main_command: is the main command
 * @new_command: is a new command
 * @next: is a pointer to the next alias
 */

typedef struct alias_t
{
	char *main_command;
	char *new_command;
	struct alias_t *next;
} alias_t;
extern alias_t *alias_list;

/**
 * struct path_t - This is a linked list containing
 * each diretory on the node
 * @dir: This is a directory Path
 * @next: is apointer to the next directory
 */

typedef struct path_t
{
	char *dir;
	struct path_t *next;
} path_t;
alias_t *get_alias_list(void);

int custom_setenv(const char *name, const char *value, int overwrite);
int custom_env(void);
int check_path(char **args);
char *custom_getenv(const char *name);
char *get_dir();
int custom_unsetenv(char **args);
path_t *link_path(void);
int execute(char *command, int line_num);
int execute_with_path(char **args);
ssize_t custom_getline(char **buffer, size_t *bufsize, int fd);
int custom_cd(char **args, int line_num);
int custom_echo(char **args);
int run_child(char **args);
int run_parent(void);
int EXT_stat(void);
char *custom_str_tok(char *command, const char *delimiter);
char *check_alias(char *neww);
int execute_alias(char *main, char **args);
int tokenify(char *command, char **args);
int built_ins(char **args, int line_num);
int built_ins2(char **args, int line_num);
int custom_strlen(const char *s);
char *custom_strcat(char *dest, const char *src);
char *custom_strcpy(char *dest, const char *src);
int echo_ppid(int printed_chars);
int echo_exit(int printed_chars);
int custom_exit(char **args);
char *custom_strdup(const char *str);
int custom_strncmp(const char *s1, const char *s2, size_t n);
void print_error(const char *cmd, const char *msg, int line_num);
char *custom_itoa(int value);
char *cd_error(char **args);
int custom_strcmp(const char *s1, const char *s2);
char *custom_strchr(const char *s, const char c);
void custom_freeenv(void);
void  custom_freeargs(char **args);
void custom_free_path(path_t *path);
int custom_alias(char **args);
int create_keyvalue_pair(alias_t **alias_list, char *args, char *equals);
alias_t *add_alias(alias_t **head, char *neww, char *main);
int printOut_alias_list(alias_t *head);
int echo_env(int printed_chars, char **args, int i);
void not_buff(void);

#endif /* MAIN_H */
