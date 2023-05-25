#include "shell.h"

/**
 * is_shell_interactive - Checks if shell is running in interactive mode.
 * @info: Pointer to info_t struct.
 *
 * Return: 1 if running interactive mode, 0 otherwise.
 * Partner project between Ben and Allan.
 */
int is_shell_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_character_delimiter - Checks if character is delimiter.
 * @c: The character to check.
 * @delimiter: The delimiter character.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_character_delimiter(char c, char delimiter)
{
	return (c == delimiter);
}

/**
 * is_character_alphabetic - Checks if a character is an alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int is_character_alphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * convert_string_to_integer - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers are present in the string,
 * the converted number otherwise.
 */
int convert_string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
