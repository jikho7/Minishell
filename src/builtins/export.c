#include "../../minishell.h"

/* -------------------------- 1.Print export -------------------------------*/
static void	print_export(char **var)
{
	int	i;
	int	j;

	i = 0;
	while (var[i])
	{
		j = 0;
		printf("declare -x ");
		while (var[i][j - 1] != '=')
			printf("%c", var[i][j++]);
		printf("\"");
		while (var[i][j])
			printf("%c", var[i][j++]);
		printf("\"\n");
		i++;
	}
}

/* -------------------- 2. Tri apha tab -----------------------*/
static void	ft_trialpha(char **env)
{
	int		i;
	int		in_order;
	char	**var;

	i = 0;
	in_order = 1;
	var = env;
	while (in_order != i)
	{
		i = 0;
		in_order = 0;
		while (var[i])
		{
			if (var[i + 1] && ft_strcmp(var[i], var[i + 1]) > -1)
			{
				ft_strswap(&var[i], &var[i + 1]);
				in_order--;
			}
			in_order++;
			i++;
		}
	}
	print_export(var);
}

/* -------------------- 3.Export without args -------------------------*/
static void	export_no_args(t_shell *info)
{
	char	**env;

	env = lst_to_tab(info->env, info);
	ft_trialpha(env);
}

/* --------------------- 4.export with $args --------------------------*/
static void	export_d(t_shell *info, int index)
{
	t_list	*node;
	t_list	*tmp;

	node = find_var_env(info->env, info->arg[index], 0);
	if (node == NULL)
		export_no_args(info);
	else
	{
		tmp = ft_dlst_newcontent(NULL, &info->trash_lst);
		str_to_node(node->valeur, tmp, info);
		ft_dlst_addback(&info->env, tmp);
	}
}

/* ------------------------- 5.Fonction export ------------------------------*/
void	export_minishell(t_shell *info)
{
	t_list	*node;
	int		i;

	i = 0;
	if (!*info->arg)
		export_no_args(info);
	else
	{
		while (info->arg[i])
		{
			if (strncmp(info->arg[i], "$", 1) == 0 && info->arg[i][1] != '\0')
				export_d(info, i);
			else if (ft_isalpha(info->arg[i][0]) == 0 || info->arg[i][0] == '$')
				printf("bash: export: `%s': not a valid identifier\n",
					info->arg[i]);
			else
			{
				node = ft_dlst_newcontent(NULL, &info->trash_lst);
				str_to_node(info->arg[i], node, info);
				ft_dlst_addback(&info->env, node);
			}
			i++;
		}
	}
}
