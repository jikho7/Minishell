#include "minishell.h"
#include <errno.h>

void	close_pipes(t_pipe *d, int process)
{
	if (process == 1)
	{
		close(d->fd_pipe1[1]);
		close(d->fd_pipe2[0]);
	}
	if (process == 2)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe2[1]);
	}
	if (process == 3)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe1[1]);
	}
	if (process == 4)
	{
		close(d->fd_pipe2[1]);
		close(d->fd_pipe2[0]);
	}
}

void handle_redirections(t_exec *exe, t_pipe *pipe)
{	
	//fprintf(stderr, ">>>HANDLE FILES\n");
	if ((ft_strncmp((const char*)exe->str_heredoc, "", 1) != 0))	// AJOUT HEREDOC
	{
		//fprintf(stderr, "heredoc no empty\n");
		pipe->fd_in = open(".heredoc.txt", O_RDONLY);	//ADDED HANDLE HEREDOC	
		exe->redi_infile[0] = ".heredoc.txt";
	}
	else
	{
		//fprintf(stderr, "heredoc empty\n");
		if (exe->redi_infile[0])
			exe->redi_infile = handle_infile(exe);
	}
	if (exe->redi_outfile[0])
		exe->redi_outfile = handle_outfile(exe);
	init_struc_pipe(pipe, exe->redi_infile[0], exe->redi_outfile[0], exe);
}

char	**handle_infile(t_exec *exe)
{
	int i;
	int in;
	char **infile_tab;

	infile_tab = ft_split_exec(exe->redi_infile[exe->idx], ' ', 0);
	i = 0;
	if (infile_tab[0])
	{
		while(infile_tab[i])
		{
			in = open(infile_tab[i], O_RDONLY, 0644);
			close(in);
			if (in == -1)
				error_infile_outfile(0, exe);
			i++;
		}
		i--;
	}
	exe->redi_infile[0] = infile_tab[i];
	//fprintf(stderr, "control redi infile: %s\n", exe->redi_infile[0]);
	return(&exe->redi_infile[0]);
}

char	**handle_outfile(t_exec *exe)
{
	int i;
	int out;
	char **outfile_tab;

	outfile_tab = ft_split_exec(exe->redi_outfile[exe->idx], ' ', 0);
	i = 0;
	if (outfile_tab[0])
	{
		while(outfile_tab[i])
		{
			out = open(outfile_tab[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(out);
			i++;
		}
		i--;
	}
	exe->redi_outfile[0] = outfile_tab[i];
	//fprintf(stderr, "control redi outfile: %s\n", exe->redi_outfile[0]);
	return(&exe->redi_outfile[0]);
}