# Operating-Systems-Labs
OS Fall 2015 Labs

**cd <directory>** - If <directory> is not present, print current directory. Display error if directory doesn't exist. Also change PWD environment variable.

**clr** - Clear the screen

**dir <directory>** - List contents of <directory>

**environ** - List all environment strings

**echo <comment>** - Display <comment> followed by new line (spaces/tabs may be reduced to single space)

**help** - Display the user manual using the `more` filter

**pause** - Pause operations until 'Enter' is pressed

**quit** - Quit the shell

Shell environment should also contain `shell=<pathname>/myshell` which is the path to the directory from which the shell was executed.

All other commands are program invocation (use `fork` and `exec` to create child processes) and should be executed in the path above.

Must take command line input from file w/ command line arguments. (i.e. `myshell batchfile` where batchfile should contain command lines to be executed, shell exits when complete)

###Optional; +10%
Must support I/O-redirection on either/both stdin/stdout:
`programname arg1 arg2 <inputfile> outputfile`
will execute `programname` with the arguments `arg1` and `arg2`, FILE streams replacing `inputfile` and `outputfile`
Should also support `dir`, `environ`, `echo`, `help` for `stdout` redirection


Must support background execution of programs with the argument `&`
