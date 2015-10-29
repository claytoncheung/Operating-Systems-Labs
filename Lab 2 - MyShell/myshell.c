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
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
//#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[], char **envp)
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
	printf("1");
    // Parse the commands provided using argc and argv
    
    //using this to test
    if (argc >= 1) {
	printf("2");
	batch(argv[1], envp);
	printf("3");
	return EXIT_SUCCESS;
    }
	printf("4");
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument

        char cwd[1024] = { 0 };
        getcwd(cwd, sizeof(cwd));

        printf("%s > ", cwd);

        strcpy(buffer, get_buffer());
        printf("%s\n", buffer);
        strcpy(command, strtok(buffer, " "));

    /*********************************/
    /********* ARG ONLY TAKEN ********/
    /********* WHEN NEEDED BY ********/
    /*********    COMMAND     ********/
    /*********************************/

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            // your code here
            strcpy(arg, strtok(NULL, " "));
        	sh_cd(arg);

        }

        else if(strcmp(command, "dir") == 0)
        {
        	dir_list();
        }
        
        else if(strcmp(command, "pause") == 0)
        {
            pause();
        }
        
        else if(strcmp(command, "help") == 0)
        {
            strcpy(arg, strtok(NULL, " "));
            help(arg);
        }
	
	else if(strcmp(command, "environ") == 0) {
		environVariable(envp);
	}
	
	//to invoke with batch file, there should be only one argument which is the name of the batch file
	//myshell exits after completing the requested commands
	/*else if (argc == 1) {
		batch(argv[1], envp);
		return EXIT_SUCCESS;
	}*/
		
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
		
		/*REMEMBER TO ADD ADDITIONAL COMMANDS TO batch FUNCTION IN utility.c*/
		
		
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual", stderr);
        }
    }
    return EXIT_SUCCESS;
}
