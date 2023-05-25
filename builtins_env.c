#include "shell.h"

/**
 * my_builtin_env - displays the environment where the shell runs
 * @my_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int my_builtin_env(data_of_program *my_data)
{
	if (my_data->tokens[1] == NULL)
	{
		print_my_environ(my_data);
		return (0);
	}

	char my_name[50] = {'\0'};
	char *my_var_copy = NULL;

	for (int i = 0; my_data->tokens[1][i]; i++)
	{
		if (my_data->tokens[1][i] == '=')
		{
			my_var_copy = str_duplicate(my_env_get_key(my_name, my_data));
			if (my_var_copy != NULL)
				my_env_set_key(my_name, my_data->tokens[1] + i + 1, my_data);

			print_my_environ(my_data);
			if (my_env_get_key(my_name, my_data) == NULL)
			{
				_print(my_data->tokens[1]);
				_print("\n");
			}
			else
			{
				my_env_set_key(my_name, my_var_copy, my_data);
				free(my_var_copy);
			}
			return (0);
		}
		my_name[i] = my_data->tokens[1][i];
	}

	errno = 2;
	perror(my_data->command_name);
	errno = 127;
	return (0);
}

/**
 * my_builtin_set_env - sets the value of an environment variable
 * @my_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int my_builtin_set_env(data_of_program *my_data)
{
	if (my_data->tokens[1] == NULL || my_data->tokens[2] == NULL)
		return (0);
	if (my_data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(my_data->command_name);
		return (5);
	}

	my_env_set_key(my_data->tokens[1], my_data->tokens[2], my_data);

	return (0);
}

/**
 * my_builtin_unset_env - removes an environment variable
 * @my_data: struct for the program's data
 * Return: zero if success, or other number if it's declared in the arguments
 */
int my_builtin_unset_env(data_of_program *my_data)
{
	if (my_data->tokens[1] == NULL)
		return (0);
	if (my_data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(my_data->command_name);
		return (5);
	}
	my_env_remove_key(my_data->tokens[1], my_data);

	return (0);
}
