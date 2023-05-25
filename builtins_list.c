#include "shell.h"

/**
 * my_builtins_list - search for a match and execute the associated builtin
 * @my_data: struct for the program's data
 *
 * Return: Returns the return value of the executed function if there is a
 * match, otherwise returns -1.
 **/
int my_builtins_list(data_of_program *my_data)
{
	int my_iterator;
	builtins my_options[] = {
		{"exit", my_builtin_exit},
		{"help", my_builtin_help},
		{"cd", my_builtin_cd},
		{"alias", my_builtin_alias},
		{"env", my_builtin_env},
		{"setenv", my_builtin_set_env},
		{"unsetenv", my_builtin_unset_env},
		{NULL, NULL}
	};

	for (my_iterator = 0; my_options[my_iterator].builtin != NULL; my_iterator++)
	{
		if (str_compare(my_options[my_iterator].builtin, my_data->command_name, 0))
			return (my_options[my_iterator].function(my_data));
	}

	return (-1);
}
