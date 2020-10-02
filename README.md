# C-Shell

This is a Linux Shell implemented in C.


## Running the Shell

`make` 
<br>
 `./shell_yeah`

## Exiting from the Shell

`quit`

## Commands

* `ls [-l -a] <dir1> <dir2>` - List files and Directory

  * `ls`: List of all the files and directories in the current directory in alphabetical order
  * `ls -a`: Hidden files
  * `ls -l`: Long listing 
  * `ls -al`/`l -la`/`ls -l -a`/`ls -a -l`: Long listing with hidden files


* `cd <dir>` - Change Directory

  * `cd ..`: Change to previous directory
  * `cd .`: Remain in current directory  
  * `cd`: Change to directory to ~/

* `echo [arguments]` - Print in Terminal

  * `echo`: Print "\n"
  * `echo "text"`: Print "text"
  * `echo 'text'`: Print 'text'
  * `echo text`: Print text

* `history [number]` - Display History of Commands

  * `history`: Last 10 commands
  * `history [1-20]`: Last n commands

* `pwd` - Present Working Directory

* `pinfo [pid]` - Process Information

  * `pinfo`: Process information about the shell
  * `pinfo <pid>`: Process information about process with given pid

* `setenv [var] [value]` - Sets value of environment variable

  * `setenv [var]`: Default value = " "
  * `setenv [var] [value]`: var = value

* `unsetenv [var]` - Unsets value of environment variable

* `jobs` - Prints a list of all running jobs

* `kjobs [job_num] [sig_num]` - Sends signal val to that process with job_num

* `overkill` - Kills all background process at once

* `bg [job_num]` - Changes a Stopped background job to a Running

* `fg [job_num]` - Brings a background job to foreground 

* `<command> &` - Run Process in Background

## Signals

* `CTRL-C` - Sends SIGINT signal to the current foreground job

## Files

* `headers.h`
  * Header files 
  * Global variables 
  * Function declarations

* `main.c`
  * main(): Main function to initialise variables and call the loop
  * shell_loop(): Runs the main loop of the code for the continuous execution of the shell

* `background.c`
  * background(): Forks the existing process and runs a child process in the background. Once the child terminates, the exit status of the child process prints on the screen.

* `foreground.c`
  * foreground(): Forks the existing process and runs a child process in the foreground. The parent process resumes once the child terminates and waits till then.

* `cd.c`
  * cd(): Changes the directory based on absolute or relative path provided

* `echo.c` 
  * echo(): Prints a string argument on the terminal (stdout). Handles cases with and without quotes.

* `ls.c`
  * ls(): Initialises flags for listing directories specified by absolute or relative path
  * print_ls(): Prints the files in directory  according to arguments

* `pinfo.c`
  * pinfo(): Prints the info of the process according to arguments
  
* `pwd.c`
  * pwd():Print the present working directory
  * tildconvertedpwd():Print the command prompts
  * tildconverter():Replaces absolute path of home directory with ~ symbol

* `history.c`
  * read_history(): Loads history from previous session.
  * update_history(): Updates history
  * history(): Prints the history according to arguments
  * write_history(): Stores last 20 commands in hist.txt

* `history.txt`
  * Stores upto 20 used commands


