```c
								// BASE //
								
int main()
{
	// ft_create_prompt; // to make tests

	ft_init_shell; // to load config files
	ft_loop_shell; // waiting for user's inputs
	{
		ft_create_prompt; // >name_of_prompt
		
		// READ THE LINE
		ft_read_line; // getline(), read commands on stdin
		{
			ft_alloc;
			if(line too long)
				ft_realloc;
		}
		// PARSING
			ft_tokenizer; // lexiquer function, creates tokens == lsh_split_line
			ft_parsing; // creates commands
			
		// EXECUTION
			ft_launch // fork()
			ft_process_or_builtins
				builtins;
				ft_execute_cmds; // fork(), excev() by a child, CLOEXEC
			free_args_n_line;
			
	}

	ft_free_n_cleans; // 
	return (EXIT_SUCCESS);
}


	/*					// TO ADD AT THE END //
	// update parsing
	 -> to handle redirections // (>)
	 -> to handle single/double quotes
	 -> to handle variable d'env // `=`
	 -> to handle_special_symbol // $!, $$, $?
	 -> to handle heredocs // <<word ...text... word
	 -> to handle tidle // ~
	
	// create builtins // echo -n, cd, pwd, export, unset, env, exit
	
	// handle signals
		-> ft_handle_cmd$; // commandes arriere plan, SIGCHILD
		-> ft_handle_jobs; // groupe de process, kill(), SIGCONT
		-> ft_handle_forground_jobs; //group process avant plan, tcsetpgrp,   SIGINT
		-> ft_jobs_control; // 		
	}
	// handle commands$, commandes d'arriere plan
	// implement ^d, ^c, ctrl-\
	*/
```

##### Fonctions autorisees

`readline`: imprime un prompt, puis lis et retourne un seule ligne de texte a l'user.

`rl_clear_history(void)`: Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
`rl_on_new_line`: Dit aux routines de mise à jour que nous avons déplacé sur une nouvelle ligne (vide), généralement après avoir ajouté une nouvelle ligne. (Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.)
`rl_replace_line (const char *text, int clear undo)`: Remplace le contenu de `rl_line_buffer` avec du texte. Le point et la marque sont preserves si possible. Si la liste d'annulation nettoyee est non-0, la liste d'annulation associee avec la ligne actuelle est nettoyee. Replace the contents of `rl_line_buffer` with text. The point and mark are preserved, if possible. If clear undo is non-zero, the undo list associated with the current line is cleared.
`rl_redisplay`: Change ce que l'ecran affiche pour refleter l'actuel contenu de `rl_line_buffer` (Change what's displayed on the screen to reflect the current contents of `rl_line_buffer`.)

`add_history(const char *string)`: Place string at the end of the history list. The associated data field (if any) is set to `NULL`. If the maximum number of history entries has been set using `stifle_history()`, and the new number of history entries would exceed that maximum, the oldest history entry is removed.

`printf`, `malloc`, `free`, `write`
`access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `exit`
`unlink`, `execve`, `dup`, `dup2`, `pipe`
`strerror`, `perror`
`getenv`

`wait3`:   Allows the calling process to obtain status information for specified child processes
`wait4`:   The wait4() subroutine is similar to the wait3() subroutine except that we can specify the process ID of the child.

`signal`: `void (*signal(int sig, void (*func)(int)))(int)`: sets a function to handle signal i.e. a signal handler with signal number `sig`.
`sigaction`: Examines, changes, or both examines and changes the action associated with a specific signal.
`sigemptyset`: Initializes the signal set pointed to by _set_
`sigaddset`: Adds the individual signal specified by the _signo_ to the signal set pointed to by set.
	What is the difference between Sigaction and Sigaddset?
		-> sigaddset is used for adding the corresponding signal mask to that sigset_t variable. In sigaction, it is not required.
`kill`: Sends a signal to a process or process group specified by pid.

`getcwd`: Determines an absolute path name of the current working directory of the calling process, and copies that path name into the array pointed to by path_name argument.
`chdir`: System call, change the current working directory.
`stat`: Used to list properties of a file identified by path.
`lstat`: Obtains file attributes similar to stat(), except when the named file is a symbolic link; in that case lstat() returns information about the link, while stat() returns information about the file the link references.
`fstat`: Obtains information about an open file known by the file descriptor fildes, obtained from a successful call to a function such as open(2), creat(2), dup(2), fcntl(2), or pipe(2).

`opendir`
`readdir`
`opendir()` opens the directory file, and mallocs one "struct dirent". `readdir()` reads the next directory entry into that one "struct dirent", and returns a pointer to it.
`closedir`: Close the directory stream referred to by the argument dirp (directotry path?)

`isatty`: Takes a file descriptor as a parameter and returns 1 if that file descriptor is associated with a terminal.
`ttyname`: Returns a string containing the path name of the terminal associated with the given file descriptor, fildes. 
`ttyslot`: Returns the index of the current user's entry in the utmpx database, in some file.
`ioctl`:   Performs the generic I/O operation command on filedes.
	The DeviceIoControl function provides a device input and output control (IOCTL) interface through which **an application can communicate directly with a device driver**. The DeviceIoControl function is a general-purpose interface that can send control codes to a variety of devices.

###### Termios functions
The termios functions describe **a general terminal interface that is provided to control asynchronous communications ports**. The termios structure Many of the functions described here have a termios_p argument that is a pointer to a termios structure.

`tcsetattr`: Set the parameters associated with the terminal referred to by the open file descriptor fildes.
`tcgetattr`: Get the parameters associated with the terminal referred to by fildes and store them in the termios structure referenced by termios_p.

###### Routine functions 
Ces routines sont incluses comme aide à la conversion pour les programmes qui utilisent la bibliothèque termcap. Leurs paramètres sont les mêmes et les routines sont émulées en utilisant la base de données terminifo. Ainsi, ils ne peuvent être utilisés que pour interroger les capacités des entrées pour lesquelles une entrée terminfo a été compilée.
`tgetent`: Loads the entry for _name_. It returns 1 on success, 0 if there is no such entry, and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer _bp_.
`tgetflag`: Gets the boolean entry for _id_.
`tgetnum`: Gets the numeric entry for _id_.
`tgetstr`: Returns the string entry for _id_. Use [tputs()](https://www.mkssoftware.com/docs/man3/curs_terminfo.3.asp) to output the returned string.
`tgoto`: Instantiates the parameters into the given capability. The output from this routine is to be passed to [tputs()](https://www.mkssoftware.com/docs/man3/curs_terminfo.3.asp).
`tputs`: It can retrieve capabilities by either termcap or terminfo name.

Except where explicitly noted, `routines` that return an integer return `ERR` upon failure and `OK` upon successful completion.
Routines that return pointers return NULL on error.

---------------------

Ne pas traiter les `\` et les `;` 
Bonus: `&&`, `||` et `*` (wildcards)

