#include "minishell.h"

void handle_single_cmd(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    int fork_pid;
	int status;

    //fprintf(stderr, "single cmd\n");
    fork_pid = fork();
    if (fork_pid == -1)
    {
        fprintf(stderr, "fork error\n");
        return;
    }
    if (fork_pid == 0)
    {
        d_exe->path = get_path(d_exe->env_cpy);
        d_exe->access_path = ft_split_exec(d_exe->path, ':', 1);
        d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
        d_exe->cmd_path = get_cmd_path(d_exe->cmd_n_arg[0], d_exe, &d_shell->trash_lst);
        handle_dup_fd_single_cmd(d_pip, d_exe);
        if (execve(d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
        {
            fprintf(stderr, "execve error\n");
            return;
        }
    }
    else
    {
        //int status;
        waitpid(fork_pid, &status, 0);
        // Handle the child process completion if needed
    }
}

void handle_dup_fd_single_cmd(t_pipe *d_pip, t_exec *exe)
{
	handle_redirections(exe, d_pip);
    if (d_pip->infile)
    {
        d_pip->fd_in = open(d_pip->infile, O_RDONLY);
        if (d_pip->fd_in == -1)
        {
            fprintf(stderr, "error opening infile\n");
            return;
        }
        if (dup2(d_pip->fd_in, STDIN_FILENO) == -1)
        {
            fprintf(stderr, "error dup IN\n");
            return;
        }
        close(d_pip->fd_in);
    }
    if (d_pip->outfile)
    {
        d_pip->fd_out = open(d_pip->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (d_pip->fd_out == -1)
        {
            fprintf(stderr, "error opening outfile\n");
            return;
        }
        if (dup2(d_pip->fd_out, STDOUT_FILENO) == -1)
        {
            fprintf(stderr, "error dup OUT\n");
            return;
        }
        close(d_pip->fd_out);
    }
}

void		child_process_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		//fprintf(stderr, ">>child proces_0: %s\n", cmd);
		close_pipes(d_pip, 1);
		d_exe->path = get_path(d_exe->env_cpy);
		d_exe->access_path = ft_split_exec(d_exe->path, ':', 1);
		d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
		d_exe->cmd_path = get_cmd_path(d_exe->cmd_n_arg[0], d_exe, &d_shell->trash_lst);
		//fprintf(stderr, "handle_redi_child_0\n");
		handle_redirections(d_exe, d_pip);
		if (d_exe->cmd_number == 0)
			first_cmd(d_pip, d_exe->cmd_path, d_exe);
		else if (d_exe->cmd_number == d_exe->number_of_pipes)
			last_cmd(d_pip, d_exe->cmd_path, 0, d_exe);
		else
			middle_cmd(d_pip, d_exe->cmd_path, 0);
		if (execve (d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
			fprintf(stderr, "error excve\n");
	}
	close_pipes(d_pip, 3);
	pipe(d_pip->fd_pipe1);
}

void	child_process_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;
	//fprintf(stderr, ">>child proces_1: %s\n", cmd);
	fork_pid = fork();

	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d, 2);
		d_exe->path = get_path(d_exe->env_cpy);
		d_exe->access_path = ft_split_exec(d_exe->path, ':', 1);
		d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
		d_exe->cmd_path = get_cmd_path(d_exe->cmd_n_arg[0], d_exe, &d_shell->trash_lst);
		//fprintf(stderr, "handle_redi_child_1\n");
		handle_redirections(d_exe, d);
		if (d_exe->cmd_number == d_exe->number_of_pipes)
		{
			fprintf(stderr, "last_cmd child_1\n");
			last_cmd(d, d_exe->cmd_path, 1, d_exe);
		}
		else
		{
			fprintf(stderr, "middle_cmd child_1\n");
			middle_cmd(d, d_exe->cmd_path, 1);
		}
		if (execve (d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
			fprintf(stderr, "error excve\n");//handle_exec_err(d->fd_pipe1[1], d_exe->cmd_n_arg, cmd_path);
	}
	close_pipes(d, 4);
	pipe(d->fd_pipe2);
}

void	first_cmd(t_pipe *d, char *cmd_path, t_exec *d_exe)
{
	//fprintf(stderr, "first_cmd\n");
	(void)cmd_path;
	(void)d_exe;
	d->fd_in = open(d->infile, O_RDONLY);
	if (d->infile)
	{
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
			fprintf(stderr, "dup in error_first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
	}
	d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->fd_out < 0)
	{
		close(d->fd_out);
		fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
	}
	if (d->outfile)
	{
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
			fprintf(stderr, "dup error_last_cmd_0\n"); //handle_dup_err(d->fd_out, d->fd_pipe1[0], d_exe->cmd_n_arg, 0);
	}
	if(dup2(d->fd_pipe2[1], STDOUT_FILENO) == -1)
			fprintf(stderr, "dup out error_first_cmd\n");
	close_pipes(d, 2);
	close(d->fd_in);
}

void	last_cmd(t_pipe *d, char *cmd_path, int process, t_exec *d_exe)
{
	//fprintf(stderr, "last_cmd\n");
	(void)cmd_path;
	(void)d_exe;
	d->fd_in = open(d->infile, O_RDONLY);
	if (d->infile)
	{
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
			fprintf(stderr, "dup in error_first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
	}
	else
	{
		if (process == 0)
		{
			if (dup2 (d->fd_pipe1[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_last_cmd_0\n"); //handle_dup_err(d->fd_out, d->fd_pipe1[0], d_exe->cmd_n_arg, 0);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_last_cmd_0\n");
		}
	}
	d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->fd_out < 0)
	{
		close(d->fd_out);
		fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
	}
	if (d->outfile)
	{
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
			fprintf(stderr, "dup error_last_cmd_0\n");
	}
	if (process == 0)
	{
		close_pipes(d, 2);
	}
	if (process == 1)
	{
		close_pipes(d, 1);
	}
	close(d->fd_out);
}

void	middle_cmd(t_pipe *d, char *cmd_path, int process)
{
	//fprintf(stderr, "middle_cmd\n");
	(void)cmd_path;
	d->fd_in = open(d->infile, O_RDONLY);
	if (d->infile)
	{
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
			fprintf(stderr, "dup in error_first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
	}
	else
	{
		if (process == 0)
		{
			if (dup2(d->fd_pipe1[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_middle_0\n");//handle_dup_err(0, d->fd_pipe1[0], d->cmd_n_arg, 1);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1) 	// A CONTROLER PIPE
				fprintf(stderr, "dup error_last_cmd_0\n");
		}
	}
	d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->fd_out < 0)
	{
		close(d->fd_out);
		fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
	}
	if (d->outfile)
	{
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
			fprintf(stderr, "dup error_last_cmd_0\n");
	}
	else
	{
		if (process == 0)
		{
			if (dup2(d->fd_pipe2[1], STDOUT_FILENO) == -1)
				fprintf(stderr, "dup error\n");//handle_dup_err(1, d->fd_pipe2[1], d->cmd_n_arg, 1);
		}
		if (process == 1)
		{
			if (dup2(d->fd_pipe1[1], STDOUT_FILENO) == -1)
				fprintf(stderr, "dup error_middle_1\n");//handle_dup_err(1, d->fd_pipe1[1], d->cmd_n_arg, 1);
			close_pipes(d, 1);
		}
	}
	if (process == 0)
		close_pipes(d, 2);
	if (process == 1)
		close_pipes(d, 1);
}