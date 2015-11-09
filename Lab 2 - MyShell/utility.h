/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */


#ifndef UTILITY_H_
#define UTILITY_H_
#include "myshell.h"



// Include your relevant functions declarations here they must start with the
// extern keyword such as in the following example:
// extern void display_help(void);

// List environment variables. char **envp expects a double-pointer to those variables
extern int environVariable(char **envp);
// Batch file for shell. Expects a file to open as char *arg, environment variables as char **envp 
extern int batch(char *arg, char **envp);
// Change directory to currentpath/arg
extern int sh_cd(char arg[BUFFER_LEN]);
// List the current working directory
extern int dir_list(void);
// Pause execution of the shell
extern int pause(void);
// Display help file. if char arg is "more", will open more help
extern int help(char arg[BUFFER_LEN]);

#endif /* UTILITY_H_ */
