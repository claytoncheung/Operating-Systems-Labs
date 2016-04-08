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


// Declare function prototypes in utility.h
// Put functions in this file.

int environVariable(char **envp) {
	// Local environment variable
	char** env = NULL;

	// Loop through environment pointer argument, if it's not zero, continue.
	for (env = envp; *env != 0; env++) {
		// Iterate through environment variables and display them.
		char* thisEnv = *env;
		printf("%s\n", thisEnv);
	}
return EXIT_SUCCESS;
}

int batch(char *arg, char **envp) {

	// Open filename specified by the user
	FILE *fp = fopen (arg, "r");

	// Declare major variables
	char line[BUFFER_LEN];
	char cmd[BUFFER_LEN]={0};
	char localArg[BUFFER_LEN]={0};

	// Loop as long as there is text entered in the shell.
	while (fgets(line, BUFFER_LEN, fp) != NULL) {
		// Tokenize line and displays the command
		// also capture any arguments if we have any.
	  strcpy(cmd, strtok(line, "\n"));
		printf("\n%s\n", line);
		strcpy(localArg, strtok(NULL, " "));

		//figure out which command is being called
		
		// Change directory
		if (strcmp(cmd, "cd") == 0) {
    	sh_cd(localArg);
    } else if (strcmp(cmd, "dir") == 0)  {
			// List directory
			dir_list();
    } else if(strcmp(cmd, "pause") == 0) {
			// Pause execution
    	pause();
    } else if(strcmp(cmd, "help") == 0) {
			// Display help
  		help(localArg);
    } else if(strcmp(cmd, "environ") == 0) {
			// List all environment variables
			environVariable(envp);
		} else if (strcmp(cmd, "quit") == 0) {
			// Exit the shell
			fclose(fp);
      return EXIT_SUCCESS;
    } else {
      // Unsupported command
			fputs("Unsupported command, use help to display the manual\n", stderr);
    }
	}
	
	// Close the file and exit
	fclose(fp);
	return EXIT_SUCCESS;
}

int sh_cd(char arg[BUFFER_LEN]) {
	// cwd - current working directory
	char cwd[1024] = { 0 };
	getcwd(cwd, sizeof(cwd));
	if(arg == NULL) {
		fprintf(stderr, "Shell: Expected directory");
	}	else {
		//Throws an error if the directory cannot be changed, lists current working directory.
		if(chdir(arg) != 0)	{
			perror("Shell");
			printf("Current Directory: %s\n", cwd);
		}
	}
	return EXIT_SUCCESS;
}

int dir_list(void) {
	//Structs from the unistd.h library for listing the directory
	DIR *d;
	struct dirent *dir;
	d = opendir(".");

	//While there are still directory contents unlisted, this loop will list them, and will close the directory at the end.
	if(d)	{
		while((dir = readdir(d)) != NULL) {
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return EXIT_SUCCESS;
}

int pause(void) {
	printf("**Execution Paused**\n");
	
	//Pauses execution of program until Enter is pressed
	fprintf(stderr, "Press [Enter] to continue...");
	
	//Get user input and return
	getchar();
	return EXIT_SUCCESS;
}

int help(char arg[BUFFER_LEN]) {
	// Declare major variables
	// If argument is "more", open helpmore.txt, otherwise open help.txt
	char ch;
	char* helpfile = strcmp(arg, "more") == 0 ? "helpmore.txt" : "help.txt";

	FILE *fp = fopen(helpfile, "r");

	//While the end of the file is not reached
	while( (ch = fgetc(fp) ) != EOF )	{
		//Prints the contents of the opened file
		printf("%c", ch);
	}
		
	fclose(fp);	
	printf("\n");
	return EXIT_SUCCESS;
}

int clr(void)
{
	system("clear");
	return EXIT_SUCCESS;
}
