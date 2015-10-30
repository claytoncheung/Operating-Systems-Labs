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

// Macros and constants here, eg: #define BUFFER_LEN 256
// Globals here, eg: char* abc = "abc";


int main(int argc, char *argv[], char **envp)
{
    // Declare major variables
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char shell_dir[BUFFER_LEN] = { 0 };
    char cwd[1024] = { 0 };

    // batchfile condition; call batch function when there are two arguments (1st is the program name, 2nd is batchfile)
    if (argc == 2) 
    {
		//passes the batchfile name and environment variables to batch, then quit.
		batch(argv[1], envp);
		return EXIT_SUCCESS;
    }

    // get current working directory, store this in shell_dir, and display
    getcwd(shell_dir, sizeof(shell_dir));
    printf("Shell = %s\nCopyright (c) 2015\n\n", shell_dir);    
    getcwd(cwd, sizeof(cwd));

    // Prompt user
    printf("%s > ", cwd);

    // Loop through user commands indefinitely
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Echo input back to user
        printf("%s\n", buffer);

        // Perform string tokenization to get command and arguments.
        strcpy(command, strtok(buffer, " "));

        // Execute the command entered by the user
        // Display environment variables
        if(strcmp(command, "environ") == 0) 
        {
            environVariable(envp);
        }
        // Change directory
        else if (strcmp(command, "cd") == 0)
        {
            strcpy(arg, strtok(NULL, " "));
        	sh_cd(arg);
        }
        // List current directory
        else if(strcmp(command, "dir") == 0)
        {
        	dir_list();
        }
        // Pause execution
        else if(strcmp(command, "pause") == 0)
        {
            pause();
        }
        // Display help file.
        else if(strcmp(command, "help") == 0)
        {
            strcpy(arg, strtok(NULL, " "));
            help(arg);
        }
        // Exit
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
        // Clear screen
        else if (strcmp(command, "clr") == 0)
        {
            clr();
        }
        // echo input
        else if (strcmp(command, "echo") == 0)
        {
            for(int i = 5; i < sizeof(buffer); i++)
            {
                arg[i-5] = buffer[i];
            }
            printf("%s\n", arg);
        }
		// ...
		// n.b.: Add additional batch functions to utility.c		
        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }

        // Finished running command, update current working directory and prompt user.
        getcwd(cwd, sizeof(cwd));
        printf("%s > ", cwd);
    }
    return EXIT_SUCCESS;
}
