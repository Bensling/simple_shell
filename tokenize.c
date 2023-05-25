/**
 * custom_tokenizer - Custom implementation of string tokenizer
 * @data: Pointer to the program's data
 * Return: An array of the different parts of the string
 */
void custom_tokenizer(data_of_program *data)
{
	char *delimiters = " \t";
	int i, j, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiters[j]; j++)
		{
			if (data->input_line[i] == delimiters[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_duplicate(custom_strtok(data->input_line, delimiters));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_duplicate(custom_strtok(NULL, delimiters));
	}
}
