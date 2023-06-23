#include "../../minishell.h"

/* ------------------------- 1.Exit with $? ------------------------------*/
static void	exit_d(t_shell *info, char **arg)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (ft_strncmp(*arg, "$?", 3) == 0)
	{
		printf("exit\n");
		exit (g_errno);
	}
	else if (ft_isalpha(arg[0][2]))
	{
		printf("minishell: exit: %s: numeric argument required\n", *info->arg);
		exit (255);
	}
	else
	{
		g_errno *= 10;
		g_errno += ft_atoi(*info->arg + 2) % 255;
		printf("exit\n");
		exit (g_errno);
	}
}

/* ------------------------- fonction exit ------------------------------*/
void	exit_minishell(t_shell *info)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (!*info->arg)
	{
		printf("exit\n");
		exit (g_errno);
	}
	else if (ft_isalpha(**info->arg))
	{
		printf("minishell: exit: %s: numeric argument required", *info->arg);
		exit (255);
	}
	else if (ft_tabsize(info->arg) > 1)
	{
		ft_error_msg(1, NULL);
		// printf("exit\n");
		// printf("minishell: exit: too many arguments\n");
		// g_errno = 1;
	}
	else if (ft_strncmp(*info->arg, "$?", 2) == 0)
		exit_d(info, info->arg);
	else
	{
		printf("exit\n");
		exit(ft_atoi(*info->arg));
	}
}

/*
Test déjà effectué:
--------------------------------------------|
1.exit = quitte le programme avec le dernier errno
2.exit 123 = quitte le programme avec erreur 123
3.exit abc = erreur 255
4.exit 123 123 = erreur 1 - trop d'arguments
5. exit 123a = erreur 255 ->> à corriger /!\






*/
