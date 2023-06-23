#include "../../minishell.h"

/* ------------------------- 1.Print env ------------------------------*/
static void	print_env(t_env *env)
{
	t_list	*node;
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	node = env->head;
	while (node != NULL)
	{
		if (env->head->if_var_env == 1)
			printf("%s=%s\n", node->variable, node->valeur);
		node = node->next;
	}
	g_errno = 0;
}

/* ------------------------- 2.Env avec args ------------------------------*/
void	env_with_arg(t_shell *info)
{
	if (ft_strncmp(*info->arg, "env", 4) == 0)
		print_env(info->env);
	else if (ft_strncmp(*info->arg, "$?", 3) == 0)
	{
		ft_error_msg(127, NULL);
		// printf("env: %d: No such file or directory\n", g_errno);
		// g_errno = 127;
	}
	else if (ft_strncmp(*info->arg, "/", 1) == 0 && !access(*info->arg, F_OK))
	{
		if (access(*(info)->arg, W_OK) != 0)
		{
			ft_error_msg(126, *info->arg);
			// printf("env: %s: Premission denied\n", *info->arg);
			// g_errno = 126;
		}
	}
	else
	{
		ft_error_msg(127, *info->arg);
		// printf("env: %s: No such file or directory\n", *info->arg);
		// g_errno = 127;
	}
}

/* ------------------------- 3.Fonction env ------------------------------*/
void	env_minishell(t_shell *info)
{
	t_list	*node;
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	node = info->env->head;
	if (*info->arg)
		env_with_arg(info);
	else
	{
		while (node != NULL)
		{
			if (info->env->head->if_var_env == 1)
				printf("%s=%s\n", node->variable, node->valeur);
			node = node->next;
		}
	}
	g_errno = 0;
}

/*
Test déjà effectué:
--------------------------------------------|
1.env = liste variable d'environnement
2.env env = idem 1
3.env env env = idem 1
4.env $? = 127: no file (error 127)
5.env 123 = 123: no file (error 127)
6.env abc = abc: no file (error 127)
7.env /bin = no access (error 126)
8.env /bin -> env $? -> env $? = error 126 puis 127
9.env $?abc -> à corriger /!\







*/
