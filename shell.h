#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>

/**
 * struct info_s - Struct to store shell information
 * @readfd: The file descriptor for reading
 *
 * Description: Additional members can be added as needed
 */
typedef struct info_s
{
	int readfd;
	/* Add any additional members as needed */
} info_t;

int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char delimiter);
int is_character_alphabetic(int c);
int convert_string_to_integer(char *s);

#endif /* SHELL_H */
