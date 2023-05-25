#include "shell.h"

/**
 * search_file - Check file exists, is not a directory, execution permissions.
 * @path: Pointer to the full file name
 *
 * Return: 0 on success, error code if it doesn't exist.
 */
int search_file(char *path);

/**
 * find_program - Find a program in the specified path.
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 if success, error code otherwise.
 */
int find_program(data_of_program *data);

/**
 * search_file - Check file exists, is not a directory, execution permissions.
 * @path: Pointer to the full file name
 *
 * Return: 0 on success, error code if it doesn't exist.
 */
int search_file(char *path)
{
	struct stat sb;

	if (stat(path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}

/**
 * find_program - Find a program in the specified path.
 * @data: Pointer to the program's data struct.
 *
 * Return: 0 if success, error code otherwise.
 */
int find_program(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **directories;

	if (!data->cmd_name)
		return (2);

	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (search_file(data->cmd_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->cmd_name);
	if (!data->tokens[0])
		return (2);

	directories = split_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}

	for (i = 0; directories[i]; i++)
	{
		directories[i] = str_concat(directories[i], data->tokens[0]);
		ret_code = search_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[i]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}
