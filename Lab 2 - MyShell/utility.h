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


extern char *get_buffer();
extern int sh_cd(char arg[BUFFER_LEN]);
extern void environVariable(char **envp);
extern int dir_list(void);

#endif /* UTILITY_H_ */
