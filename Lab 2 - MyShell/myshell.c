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
    char shell_dir[BUFFER_LEN] = { 0 };

    // Parse the commands provided using argc and argv
    //batchfile condition; call batch function when there are two arguments (1st is the program name, 2nd is batchfile)
    if ( argc ==2) {
		//passes the batchfile name and environment variables to batch
		batch(argv[1], envp);
		//quit shell when complete
		return EXIT_SUCCESS;
    }
    // Perform an infinite loop getting command input from users
    getcwd(shell_dir, sizeof(shell_dir));
    printf("Shell = %s\nCopyright (c) 2015\n\n", shell_dir);

    char cwd[1024] = { 0 };
    getcwd(cwd, sizeof(cwd));

    printf("%s > ", cwd);


    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
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
		
		//list all environment variables
		else if(strcmp(command, "environ") == 0) {
			environVariable(envp);
		}
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
		else if (strcmp(command, "echo") == 0)
        {
            for(int i = 5; i < sizeof(buffer); i++)
            {
                arg[i-5] =  buffer[i];
            }
            printf("%s\n", arg);
        }
		/*REMEMBER TO ADD ADDITIONAL COMMANDS TO batch FUNCTION IN utility.c*/
		
		
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
        getcwd(cwd, sizeof(cwd));
        printf("%s > ", cwd);
    }
    return EXIT_SUCCESS;
}
