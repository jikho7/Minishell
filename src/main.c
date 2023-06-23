#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{

 	(void) ac;
 	(void) av;
 	t_shell infos;
	//int i = 0;

 	t_exec	*info_exec = NULL;
	info_exec = &(t_exec){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	/*------------------VARIABLES_TEST--------------------*/
	char *test_tab_cmd[] = {"cat -e", NULL};
	char *redirections_infile[] = {"text_c.txt text_a.txt", NULL};	//"text_a.txt", "text_b.txt"
	char *redirections_outfile[] = {"", NULL};
	char *redirections_heredoc[] = {NULL};
	/*---------------------------------------------------*/

	info_exec->number_of_pipes = 0;
	info_exec->tab_cmd = test_tab_cmd;

	info_exec->env_cpy = envp;
	info_exec->redi_infile = redirections_infile;
	info_exec->redi_outfile = redirections_outfile;
	info_exec->heredoc = redirections_heredoc;
	info_exec->idx = 0;

 	shell_execution(info_exec, envp, &infos);
	//infos.status = shell_execution(infos.arg, info);
}

/* -------------------- Main principale ----------------------------*/
/*int	main(int ac, char **av, char **envp)
{
	int			check;
	t_shell		info;
	char		*buffer;

	if (ac == 1) // Sans arg = minishell
	{
		(void) av;
		init_shell(&info, envp);
		while (1)
		{
			rl_on_new_line();
			buffer = readline("> ");
			check = parse_shell (buffer, &info);
			if (check == 1)
			{
				printf("Erreur: nombre quote invalide\n");
				tok_clearlst(&info.token);
			}
			else if (check == 2)
				tok_clearlst(&info.token);
			else
			{
				print_token(&info.token, "Token");
				tok_clearlst(&info.token);
			}
		}
	}
	else if (ac == 2) // avec arg = version Debbug
	{
		buffer = "salut\"hello\"salut";
		init_shell(&info, envp);
		check = parse_shell (buffer, &info);
		if (check == 1)
			printf("Erreur: nombre quote invalide\n");
		else if (check == 2)
			tok_clearlst(&info.token);
		else
		{
			print_token(&info.token, "Token");
			tok_clearlst(&info.token);
		}
	}
	return (0);
}
*/