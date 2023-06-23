#include "../../minishell.h"

/* ------------------- 1. Str to node --------------------*/
void	str_to_node(char *str, t_list *node, t_shell *info)
{
	char	**tab;

	if (found_char(str, '=') > 0)
	{
		if (found_char(str, '=') == 1)
			tab = ft_split(str, '=', &info->trash_lst);
		else
			tab = ft_split_var(str);
		fill_node(node, ft_strdup(tab[0], &info->trash_lst),
			ft_strdup(tab[1], &info->trash_lst), 1);
		ft_free_2da(tab, NULL);
	}
	else
		fill_node(node, ft_strdup(str, &info->trash_lst), NULL, 0);
}

/* -------------------- 2. Fill node -----------------------*/
void	fill_node(t_list *node, char *s1, char *s2, int if_var)
{
	node->variable = s1;
	node->valeur = s2;
	node->if_var_env = if_var;
}

/* -------------------- 3.Find Variable env. -----------------------*/
t_list	*find_var_env(t_env *env, char *var, int if_dd)
{
	t_list	*node;

	node = env->head;
	if (if_dd == 0)
		var++;
	while (node != NULL)
	{
		if (ft_strlen(var) == ft_strlen(node->variable))
			if (ft_strncmp(var, node->variable,
					ft_strlen(var)) == 0)
				return (node);
		node = node->next;
	}
	return (NULL);
}

/* ---------------------------- 4.list to tab --------------------------------*/
char	**lst_to_tab(t_env *lst, t_shell *info)
{
	char		**tab;
	t_list		*node;
	size_t		i;
	int			var;
	int			val;

	tab = my_malloc((lst->len + 1), sizeof(char *), &info->trash_lst);
	if (!tab)
		return (NULL);
	node = lst->head;
	i = 0;
	while (node != NULL)
	{
		var = ft_strlen(node->variable) + 1;
		val = ft_strlen(node->valeur) + 1;
		tab[i] = my_malloc((var + val), sizeof(char), &info->trash_lst);
		if (!tab[i])
			return (NULL);
		tab[i] = ft_strjoin(node->variable, "=", &info->trash_lst);
		tab[i] = ft_strjoin(tab[i], node->valeur, &info->trash_lst);
		i++;
		node = node->next;
	}
	return (tab);
}

/* ------------------------- 5. Tab to list ---------------------------*/
void	tab_to_lst(t_shell *info, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_dlst_newcontent(NULL, &info->trash_lst);
		str_to_node(envp[i], node, info);
		ft_dlst_addback(&info->env, node);
		node = NULL;
		i++;
	}
}
