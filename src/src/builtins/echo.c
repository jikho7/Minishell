#include "../../minishell.h"

/* -------------------- 1->Print echo -----------------------*/
static void	print_echo(char *str, t_list *node)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (node)
		printf("%s", node->valeur);
	else if (ft_strncmp(str, "$", 1) == 0 && ft_isalnum(str[1]))
	{
		if (ft_strlen(str) > 2)
			printf("%s\n", str + 2);
		else
			return ;
	}
	else if (ft_strncmp(str, "$?", 2) == 0)
	{
		printf("%d", g_errno);
		printf("%s\n", str + 2);
	}
	else
		printf("%s", str);
}

/* -------------------- 2->$$ args -----------------------*/
static void	echo_dd(t_shell *info, char *str)
{
	char	**tab;
	//char	**tmp;
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	tab = ft_split(str, '$', &info->trash_lst);
	//tmp = tab;
	while (*tab)
	{
		if (ft_strncmp(*tab, "?", 1) == 0)
			printf("%d", g_errno);
		else if (!ft_isalnum(**tab))
			printf("$%s\n", *tab);
		else
		{
			if (find_var_env(info->env, *tab, 1) == NULL)
				printf("$");
			print_echo(*tab, find_var_env(info->env, *tab, 1));
		}
		tab++;
	}
}

/* -------------------- 3->Option "-n" -----------------------*/
static void	echo_n(t_shell *info, int g_errno, int option_n)
{
	int		i;
	i = option_n;
	while (info->arg[i])
	{
		if (found_char(info->arg[i], '$') == 1)
		{
			if (ft_strncmp(info->arg[i], "$?", 3) == 0)
				printf("%d", g_errno);
			else
				print_echo(info->arg[i],
					find_var_env(info->env, info->arg[i], 0));
		}
		else if (found_char(info->arg[i], '$') > 1)
			echo_dd(info, info->arg[i]);
		else
			print_echo(info->arg[i], NULL);
		if (info->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
}

/* -------------------- 4->Echo -----------------------*/
void	echo_minishell(t_shell *info)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (!*info->arg)
		printf("\n");
	else
	{
		if (ft_strncmp(*info->arg, "-n", 3) == 0)
			echo_n(info, g_errno, 1);
		else
			echo_n(info, g_errno, 0);
	}
}

/*
Test déjà effectué:
--------------------------------------------|
1.echo = '\n'
2.echo salut = salut
3.echo $? = 0 -> if erreur avant = errno
4.echo $NOM_VARIABLE = valeur variable ($USER = nrossel)
5.echo $?$?$?$? = 0000
6.echo $?1 = 01
8.echo $USER$? = nrossel0
9.echo $USER$abc = nrossel ->> à corriger /!\
10. echo $salut = '\n' ->> à corriger /!\







*/