/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
//#include "myshell.c"


// Define your utility functions here, these will most likely be functions that you call
// in your myshell.c source file

//Takes in command from terminal prompt, including whitespace
char *get_buffer(void)
{
	char buffer[BUFFER_LEN];
	int pos = 0;
	int c;

	//Throws an error if the buffer is empty
	if(!buffer)
	{
		fprintf(stderr, "Shell; Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	//Continously loops until told to return a value
	while(1)
	{
		//takes the iput character by character and stores as an integer, then reconstructs the input as a string. Returns string to call
		c=getchar();

		if(c==EOF||c=='\n')
		{
			buffer[pos] = '\0';
			return buffer;
		}
		else
		{
			buffer[pos] = c;
		}
		pos++;
	}

}

//Uses envp passed from main function
int environVariable(char **envp) {
	char** env = NULL;
	//prints all environment variables passed from main function
	for (env = envp; *env != 0; env++)
	{
		char* thisEnv = *env;
		printf("%s\n", thisEnv);
	}
return EXIT_SUCCESS;
}

//Uses arguments passed from main function; argument should be the filename and environment variables
int batch(char *arg, char **envp) {
	//Open batch file specified by user
	FILE *fp = fopen (arg, "r");

	//Holds our command and arguments
	char line[BUFFER_LEN];
	char cmd[BUFFER_LEN]={0};
	char localArg[BUFFER_LEN]={0};

	while (fgets(line, BUFFER_LEN, fp) != NULL) {
	//tokenize line and displays the command
    strcpy(cmd, strtok(line, "\n"));
	printf("\n%s\n", line);

	//figure out which command is being called
	if (strcmp(cmd, "cd") == 0)
        {
		strcpy(localArg, strtok(NULL, " "));
       	sh_cd(localArg);
        }

        else if(strcmp(cmd, "dir") == 0)
        {
        	dir_list();
        }
        
        else if(strcmp(cmd, "pause") == 0)
        {
            pause();
        }
        
        else if(strcmp(cmd, "help") == 0)
        {
            strcpy(localArg, strtok(NULL, " "));
            help(localArg);
        }
		
		//list all environment variables
		else if(strcmp(cmd, "environ") == 0) {
			environVariable(envp);
		}

        // quit command -- exit the shell
        else if (strcmp(cmd, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
		/* ADD ANY OTHER ADDITIONAL COMMANDS HERE
		
		
		
		
		*/
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

	}
	
	fclose(fp);
	return EXIT_SUCCESS;
}

//Changes the working directory to the arugment given.
int sh_cd(char arg[BUFFER_LEN])
{
	char cwd[1024] = { 0 };
	getcwd(cwd, sizeof(cwd));
	if(arg == NULL)
	{
		fprintf(stderr, "Shell: Expected directory");
	}
	
	//Throws an error if the directory cannot be changed, lists current working directory.
	else
	{
		if(chdir(arg) != 0)
		{
			perror("Shell");
			printf("Current Directory: %s\n", cwd);
		}
	}
	return EXIT_SUCCESS;
}

//Lists directory contents.
int dir_list(void)
{
	//Structs from the unistd.h library for listing the directory
	DIR *d;
	struct dirent *dir;
	d = opendir(".");

	//While there are still directory contents unlisted, this loop will list them, and will close the directory at the end.
	if(d)
	{
		while((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return EXIT_SUCCESS;
}

int pause(void)
{
	printf("**Execution Paused**\n");
	
	//Pauses execution of program until Enter is pressed
	fprintf(stderr, "Press [Enter] to continue...");
	
	//Gets user input
	getchar();

	//Returns to main program
	return EXIT_SUCCESS;

}

int help(char arg[BUFFER_LEN])
{

	char ch;

	//If 'more' is entered after 'help'
	if(strcmp(arg, "more") == 0)
	{
		//Opens the 'helpmore' file
		FILE *fp = fopen("helpmore.txt", "r");

		//While the end of the file is not reached
		while( (ch = fgetc(fp) ) != EOF )
		{
			//Prints the contents of the 'helpmore' file
			printf("%c", ch);
		}
		fclose(fp);
	}
	

	else
	{
		//Opens the 'help' file
		FILE *fp = fopen("help.txt", "r");

		//While the end of the file is not reached
		while( (ch = fgetc(fp)) != EOF )
		{
			//Prints the contents of the 'help' file
			printf("%c", ch);
		}
		fclose(fp);	
	}
	
	printf("\n");
	return EXIT_SUCCESS;
}
