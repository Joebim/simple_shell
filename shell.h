#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for change_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passnum - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_f: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passnum
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_f;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} num_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command f
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(num_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(num_t *, char **);
int find_builtin(num_t *);
void find_cmd(num_t *);
void fork_cmd(num_t *);

/* toem_parser.c */
int command_check(num_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(num_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void char_put(char *);
int char_print(char);
int print_format(char c, int fd);
int print_formats(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toemint_convert.c */
int interactive(num_t *);
int de_lim(char, char *);
int alpha_check(int);
int int_convert(char *);

/* toem_errors1.c */
int convert_err(char *);
void print_error(num_t *, char *);
int print_d(int, int);
char *change_num(long int, int, int);
void omit_signs(char *);

/* toem_builtin.c */
int exit_c(num_t *);
int cmd_cd(num_t *);
int set_h(num_t *);

/* toem_builtin1.c */
int hist(num_t *);
int set_user(num_t *);

/*toem_getline.c */
ssize_t get_input(num_t *);
int _getline(num_t *, char **, size_t *);
void handle_chars(int);

/* toem_getnum.c */
void clear_num(num_t *);
void set_num(num_t *, char **);
void free_num(num_t *, int);

/* toem_environ.c */
char *_getenv(num_t *, const char *);
int _myenv(num_t *);
int _mysetenv(num_t *);
int _myunsetenv(num_t *);
int env_store(num_t *);

/* toem_getenv.c */
char **env_p(num_t *);
int _unsetenv(num_t *, char *);
int _setenv(num_t *, char *, char *);

/* toem_history.c */
char *get_history_file(num_t *num);
int write_history(num_t *num);
int read_history(num_t *num);
int build_history_list(num_t *num, char *buf, int linecount);
int renumber_history(num_t *num);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *input_limit(list_t **, const char *, int);
size_t int_print_str(const list_t *);
int node_del(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t num_length(const list_t *);
char **convert_list(list_t *);
size_t int_print(const list_t *);
list_t *node_sw(list_t *, char *, char);
ssize_t find_index_n(list_t *, list_t *);

/* toem_vars.c */
int is_chain(num_t *, char *, size_t *);
void check_chain(num_t *, char *, size_t *, size_t, size_t);
int replace_alias(num_t *);
int replace_vars(num_t *);
int replace_string(char **, char *);

#endif

