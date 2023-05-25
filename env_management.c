#include "shell.h"

/**
 * get_env_value - retrieves the value of an environment variable
 * @key: the name of the environment variable
 * @data: struct containing program data
 *
 * Return: pointer to the value of the variable, or NULL if not found
 */
char *get_env_value(char *key, data_of_program *data)
{
	int i, key_length = 0;

	if (key == NULL || data->environment == NULL)
		return (NULL);

	key_length = str_length(key);

	for (i = 0; data->environment[i]; i++)
	{
		if (str_compare(key, data->environment[i], key_length) &&
		    data->environment[i][key_length] == '=')
		{
			return (data->environment[i] + key_length + 1);
		}
	}

	return (NULL);
}

/**
 * set_env_value - sets or creates an environment variable
 * @key: name of the variable to set
 * @value: new value
 * @data: struct containing program data
 *
 * Return: 1 if parameters are NULL, 2 if there is an error, or 0 if success
 */
int set_env_value(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->environment == NULL)
		return (1);

	key_length = str_length(key);

	for (i = 0; data->environment[i]; i++)
	{
		if (str_compare(key, data->environment[i], key_length) &&
		    data->environment[i][key_length] == '=')
		{
			is_new_key = 0;
			free(data->environment[i]);
			break;
		}
	}

	data->environment[i] = str_concat(str_duplicate(key), "=");
	data->environment[i] = str_concat(data->environment[i], value);

	if (is_new_key)
	{
		data->environment[i + 1] = NULL;
	}

	return (0);
}

/**
 * remove_env_key - removes an environment variable
 * @key: the key to remove
 * @data: struct containing program data
 *
 * Return: 1 if the key was removed, 0 if the key does not exist
 */
int remove_env_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	if (key == NULL || data->environment == NULL)
		return (0);

	key_length = str_length(key);

	for (i = 0; data->environment[i]; i++)
	{
		if (str_compare(key, data->environment[i], key_length) &&
		    data->environment[i][key_length] == '=')
		{
			free(data->environment[i]);

			i++;
			for (; data->environment[i]; i++)
			{
				data->environment[i - 1] = data->environment[i];
			}

			data->environment[i - 1] = NULL;
			return (1);
		}
	}

	return (0);
}

/**
 * print_environment - prints the current environment
 * @data: struct containing program data
 *
 * Return: nothing
 */
void print_environment(data_of_program *data)
{
	int i;

	for (i = 0; data->environment[i]; i++)
	{
		_print(data->environment[i]);
		_print("\n");
	}
}
