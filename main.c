#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: Number of arguments received from the command line
 * @argv: Array of arguments received from the command line
 * @env: Environment variables
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	ProgramData data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initializeProgramData(data, argc, argv, env);

	signal(SIGINT, handleCtrlC);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		/* We are in the terminal, interactive mode */
		errno = 2;
		prompt = PROMPT_MSG;
	}

	errno = 0;
	runShell(prompt, data);

	return (0);
}

/**
 * handleCtrlC - Handles the SIGINT signal (Ctrl+C)
 * @opr: Unused parameter
 */
void handleCtrlC(int opr __attribute__((unused)))
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initializeProgramData - Initializes the program data structure
 * @data: Pointer to the program data structure
 * @argc: Number of arguments received from the command line
 * @argv: Array of arguments received from the command line
 * @env: Environment variables
 */
void initializeProgramData(ProgramData *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->programName = argv[0];
	data->inputLine = NULL;
	data->commandName = NULL;
	data->execCounter = 0;

	/* Define the file descriptor to be read */
	if (argc == 1)
		data->fileDescriptor = STDIN_FILENO;
	else
	{
		data->fileDescriptor = open(argv[1], O_RDONLY);
		if (data->fileDescriptor == -1)
		{
			_printe(data->programName);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}

	data->tokens = NULL;

	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
			data->env[i] = strDuplicate(env[i]);
	}
	data->env[i] = NULL;
	env = data->env;

	data->aliasList = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
		data->aliasList[i] = NULL;
}

/**
 * runShell - Runs the shell in an infinite loop
 * @prompt: Prompt to be printed
 * @data: Pointer to the program data structure
 */
void runShell(char *prompt, ProgramData *data)
{
	int errorCode = 0, stringLen = 0;

	while (++(data->execCounter))
	{
		_print(prompt);
		errorCode = stringLen = _getline(data);

		if (errorCode == EOF)
		{
			freeAllData(data);
			exit(errno);
		}

		if (stringLen >= 1)
		{
			expandAlias(data);
			expandVariables(data);
			tokenize(data);

			if (data->tokens[0])
			{
				/* If a command is given, execute it */
				errorCode = execute(data);
				if (errorCode != 0)
					_printError(errorCode, data);
			}

			freeRecurrentData(data);
		}
	}
}
