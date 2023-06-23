#include "minishell.h"


void	init_struc_exec(t_exec *d, t_shell infos, char **env)
{
	(void)infos;
	d->env_cpy = env;
}

void	init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exec *exe)
{
	(void)exe;
	d->infile = infile;
	d->outfile = outfile;
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2])
{
	if (pipe(*fd1) == -1 || pipe(*fd2) == -1)
		fprintf(stderr, "error handles_pipes\n");
}
