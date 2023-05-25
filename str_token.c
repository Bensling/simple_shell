/**
 * custom_strtok - Custom implementation of strtok function
 * @str: The string to be tokenized
 * @delim: The delimiter characters
 * Return: A pointer to the created token
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *saved_str;
	char *token;
	int i, j;

	if (str != NULL)
		saved_str = str;

	if (saved_str == NULL || *saved_str == '\0')
		return (NULL);

	token = saved_str;
	for (i = 0; saved_str[i] != '\0'; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (saved_str[i] == delim[j])
			{
				saved_str[i] = '\0';
				saved_str = &(saved_str[i + 1]);
				return (token);
			}
		}
	}

	saved_str = NULL;
	return (token);
}
