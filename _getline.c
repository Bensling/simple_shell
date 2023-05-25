/**
 * custom_getline - Read one line from the prompt.
 * @data: Struct for the program's data
 *
 * Return: Number of bytes read.
 */
int custom_getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands[10] = {NULL};
	static char operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* Check if no more commands exist in the array */
	/* and check the logical operators */
	if (!commands[0] || (operators[0] == '&' && errno != 0) ||
		(operators[0] == '|' && errno == 0))
	{
		/* Free the memory allocated in the array if it exists */
		for (i = 0; commands[i]; i++)
		{
			free(commands[i]);
			commands[i] = NULL;
		}

		/* Read from the file descriptor into buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* Split lines by \n or ; */
		i = 0;
		do {
			commands[i] = str_duplicate(custom_strtok(i ? NULL : buff, "\n;"));
			/* Checks and splits for && and || operators */
			i = custom_check_logic_ops(commands, i, operators);
		} while (commands[i++]);
	}

	/* Obtain the next command (command 0) and remove it from the array */
	data->input_line = commands[0];
	for (i = 0; commands[i]; i++)
	{
		commands[i] = commands[i + 1];
		operators[i] = operators[i + 1];
	}

	return (str_length(data->input_line));
}

/**
 * custom_check_logic_ops - Checks and splits for && and || operators
 * @commands: Array of commands
 * @i: Index in the commands array to be checked
 * @operators: Array of logical operators for each previous command
 *
 * Return: Index of the last command in the commands array.
 */
int custom_check_logic_ops(char *commands[], int i, char operators[])
{
	char *temp = NULL;
	int j;

	/* Check for the & char in the command line */
	for (j = 0; commands[i] != NULL  && commands[i][j]; j++)
	{
		if (commands[i][j] == '&' && commands[i][j + 1] == '&')
		{
			/* Split the line when chars && are found */
			temp = commands[i];
			commands[i][j] = '\0';
			commands[i] = str_duplicate(commands[i]);
			commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands[i][j] == '|' && commands[i][j + 1] == '|')
		{
			/* Split the line when chars || are found */
			temp = commands[i];
			commands[i][j] = '\0';
			commands[i] = str_duplicate(commands[i]);
			commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
