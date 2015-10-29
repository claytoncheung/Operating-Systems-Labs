README for MyShell Project for the SOFE3950U Operating Systems Lab -- Version 1.0
Date: October 29, 2015

INTRODUCTION
-----------

This is a Command Line Interpreter with simple internal commands done for the SOFE3950U Operating Systems Lab at the University of Ontario Institute of Technology.
This "MyShell" project allows the user to enter commands into a shell and execute those commands. A look at those commands can be found in the "help.txt" file, or by typing <help> into the shell.

FILE LIST
---------

Makefile	    Makefile to build myshell
help.txt	    Includes a list of commands and their use
helpmore.txt	An in-depth look into each command and how to use them
myshell.c	    Driver for myshell
myshell.exe	  Executable file in order to use myshell
myshell.h	    myshell header file
utility.c	    Implementation of the commands and functions used in myshell
utility.h	    utility header file

SHELL COMMANDS
--------------

These shell commands are defined internally. Type 'help' in the shell to see this list.
Type 'help more' in the shell to see a more detailed explanation for each command.

Below is a list of all the commands and syntax as well as their functionalities:

cd-		      cd <directory>		Change the current default directory to <directory>
dir-	    	dir <directory>		Lists the contents of the directory <directory>
echo-	    	echo <comment>		Displays <comment> on the display
environ-  	environ			      Lists all the environment strings
pause-	  	pause			        Pauses operation of the shell 
clr-	   	  clr			          Clears the screen
quit-	    	quit			        Quits the shell

CONTRIBUTORS
------------

Name			              Student Number
Malek Mustapha-Abdullah	100541476
Clayton Cheung
Neil Ramdath
Dominick Mancini		
Scott McLean

COPYRIGHT
---------

The MIT License (MIT)

Copyright (c) [2015] 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

