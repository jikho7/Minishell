#include "../../minishell.h"

/* -------------------- 1.If $ on d_quote ----------------------------*/
static char	*ft_quote_d(char *str, t_env *env, t_dlist **trash)
{
	int		i;
	int		j;
	int		k;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	tmp[0] = NULL;
	while (!ft_isquote(str[i]))
	{
		if (str[i] == '$')
		{
			tmp[0] = ft_substr(str, 0, i, trash);
			j = 0;
			while (!ft_isquote(str[i + j]) && str[i + j] != ' ' && str[i + j] != '$' && str[i + j])
				j++;
			if (str[i + j] == ' ' || str[i + j] == '$')
			{
				k = 0;
				while (!ft_isquote(str[i + j + k]))
					k++;
				tmp[1] = ft_substr(str + (i + j), 0, k, trash);
			}
			tmp[2] = ft_substr(str, i, j, trash);
			ret = find_var_env(env, tmp[2], 0);
			if (ret)
				tmp[0] = ft_strjoin(tmp[0], ret->valeur, trash);
			if (k > 0)
				tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
		}
		i++;
	}
	return (tmp[0]);
}

/* -------------------- 2.Double quote function ----------------------------*/
char	*ft_dquote(char *str, t_shell *info)
{
	int		i;
	int		check;
	char	*tmp;
	t_tok	*token;

	check = ft_checkquote(str);
	if (check != 0)
		return (NULL);
	if (found_char(str, '$') > 0)
		tmp = ft_quote_d(str + 1, info->env, &info->trash_lst);
	i = 1;
	while (!ft_isquote(str[i]))
		i++;
	if (!tmp)
		token = new_node(ft_substr(str, 1, i - 1,
					&info->trash_lst), D_QUOTE, &info->trash_lst);
	else
		token = new_node(ft_substr(tmp, 0, ft_strlen(tmp),
					&info->trash_lst), D_QUOTE, &info->trash_lst);
	tok_addlst(&info->token, token);
	i++;
	return (str + i);
}

/* -------------------- 3.Simple quote function ----------------------------*/
char	*ft_squote(char *str, t_shell *info)
{
	int		i;
	int		check;
	t_tok	*token;

	check = ft_checkquote(str);
	if (check != 0)
		return (NULL);
	i = 1;
	while (!ft_isquote(str[i]))
		i++;
	token = new_node(ft_substr(str, 1, i - 1,
					&info->trash_lst), S_QUOTE, &info->trash_lst);
	tok_addlst(&info->token, token);
	i++;
	return (str + i);
}
