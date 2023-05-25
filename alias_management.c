/**
 * custom_print_alias - Add, remove, or show aliases
 * @data: Struct for the program's data
 * @alias_name: Name of the alias to be printed
 *
 * Return: Zero if successful, other number if it's declared in the arguments
 */
int custom_print_alias(data_of_program *data, char *alias_name)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = custom_str_length(alias_name);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias_name ||
				(custom_str_compare(data->alias_list[i], alias_name, alias_length) &&
				 data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				custom_buffer_add(buffer, "'");
				custom_buffer_add(buffer, data->alias_list[i] + j + 1);
				custom_buffer_add(buffer, "'\n");
				_custom_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * custom_get_alias - Get the value of an alias
 * @data: Struct for the program's data
 * @alias_name: Name of the requested alias
 *
 * Return: The value of the alias if found, or NULL if not found
 */
char *custom_get_alias(data_of_program *data, char *alias_name)
{
	int i, alias_length;

	/* Validate the arguments */
	if (alias_name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = custom_str_length(alias_name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (custom_str_compare(alias_name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			/* Return the value of the alias */
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	/* Return NULL if not found */
	return (NULL);
}

/**
 * custom_set_alias - Add or override an alias
 * @alias_string: Alias to be set in the form (name='value')
 * @data: Struct for the program's data
 *
 * Return: Zero if successful, other number if it's declared in the arguments
 */
int custom_set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* Validate the arguments */
	if (alias_string == NULL || data->alias_list == NULL)
		return (1);

	/* Iterate through the alias string to find the = character */
	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			/* Search if the value of the alias is another alias */
			temp = custom_get_alias(data, alias_string + i + 1);
			break;
		}
	}

	/* Iterate through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_list[j]; j++)
	{
		if (custom_str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			/* If the alias already exists, free the previous value */
			free(data->alias_list[j]);
			break;
		}
	}

	/* Add or override the alias */
	if (temp)
	{
		/* If the alias already exists, update its value */
		custom_buffer_add(buffer, "=");
		custom_buffer_add(buffer, temp);
		data->alias_list[j] = custom_str_duplicate(buffer);
	}
	else
	{
		/* If the alias does not exist, add it to the list */
		data->alias_list[j] = custom_str_duplicate(alias_string);
	}

	return (0);
}
