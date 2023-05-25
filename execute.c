#include "shell.h"

/**
 * execute_command - executes a command with its full path variables
 * @data: pointer to the program's data
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(data_of_program *data)
{
	int retval = 0, status;
	pid_t pid;

	retval = check_builtin_commands(data);
	if (retval != -1)
		return (retval);

	retval = find_program_path(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			retval = execute_process(data);
			if (retval == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}

	return (0);
}

/**
 * execute_process - executes the child process
 * @data: pointer to the program's data
 *
 * Return: 0 on success, -1 on failure
 */
int execute_process(data_of_program *data)
{
	int retval = 0;

	retval = execve(data->tokens[0], data->tokens, data->environment);
	return (retval);
}
