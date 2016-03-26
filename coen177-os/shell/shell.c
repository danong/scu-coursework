// basic programming task:
//
// this is a very simple unix-like shell written in c.
// it uses fork() and exec() to create and execute new
// processes. getline() is used to get the input commands
// and strtok() is used to tokenize the input to get the 
// parameters. the program loops until the exit command
// is given. both the command and parameter variables are
// dynamically allocated to prevent buffer overflows.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

// tokenizes a string, delimited by spaces. returns an array of strings
char **tokenize(char *line)
{
	int buffersize = 20, position = 0;
	char **tokens = malloc(buffersize * sizeof(char*));
	char *token;

	token = strtok(line, " ");
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= buffersize)
		{
			buffersize += 5;
			tokens = realloc(tokens, buffersize * sizeof(char*));
		}
		token = strtok(NULL, " ");
	}
	tokens[position] = NULL;
	return tokens;
}


int main()
{
	char *command;		// using getline to alloc space
	char **parameters;	
	int status;		
	size_t buffsize = 0;	// getline will malloc as needed

	while(1)
	{
		command = NULL;
		printf("$ ");
		getline(&command, &buffsize, stdin);

		command[strlen(command)-1] = '\0';

		// tokenize command for parameters
		parameters = tokenize(command);


		// EXECUTE COMMAND
		if (!strcmp(command, "exit"))
		{
			exit(1);
		}
		
		if (fork() != 0) 
		{
			waitpid(-1, &status, 0);
		}
		else
		{
			status = execvp(command, parameters);
			if (status == -1)
			{
				printf("ERROR\n");
				exit(1);
			}
		}
		free(command);
		
	}
	return 0;
}
