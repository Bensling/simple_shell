#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

typedef struct info_s
{
	int readfd;
	/* Add any additional members as needed */
} info_t;

int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char delimiter);
int is_character_alphabetic(int c);
int convert_string_to_integer(char *s);

/**
 * struct data_of_program - Holds program information and data
 * @program_name: Name of the program
 * @input_line: Buffer for input line
 * @command_name: Name of the current command
 * @file_descriptor: File descriptor for input
 * @tokens: Array of command tokens
 * @env: Array of environment variables
 * @alias_list: Array of alias names
 * @exec_counter: Execution counter
 */
typedef struct data_of_program
{
	char *program_name;
	char *input_line;
	char *command_name;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
	int exec_counter;
} data_of_program;

extern char **environ;

/* main.c */
int main(int argc, char *argv[], char *env[]);
void handle_ctrl_c(int opr);
void initialize_data(data_of_program *data, int argc, char *argv[], char **env);
void run_shell(char *prompt, data_of_program *data);

/* string_functions.c */
int _putchar(char c);
int _strlen(char *s);
void _print(char *str);
void _print_error(int error_code, data_of_program *data);
char *str_duplicate(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strstr(char *haystack, char *needle);

/* memory_functions.c */
void free_all_data(data_of_program *data);
void free_recurrent_data(data_of_program *data);

/* utility_functions.c */
void _error(data_of_program *data);
int _isalpha(int c);
int _isdigit(int c);
int _islower(int c);
int _isupper(int c);
void _printe(char *str);
void _printint(int n);

/* getline.c */
int _getline(data_of_program *data);

/* alias_functions.c */
void expand_alias(data_of_program *data);
void handle_alias(data_of_program *data, char *token);
int custom_print_alias(data_of_program *data, char *alias_name);
char *custom_get_alias(data_of_program *data, char *alias_name);
int custom_set_alias(char *alias_string, data_of_program *data);

/* variable_functions.c */
void expand_variables(data_of_program *data);

/* tokenize.c */
void tokenize(data_of_program *data);

/* execute.c */
int execute(data_of_program *data);

#endif /* SHELL_H */
