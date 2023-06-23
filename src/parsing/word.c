// #include "../../minishell.h"

// static int	check_char(char c)
// {
// 	if (ft_isprint(c) == 1 && c != ' '
// 			&& c != '\'' && c != '\"')
// 			return (1);
// 	return (0);
// }

// static char	*ft_word_d(char *str, t_env *env, t_dlist **trash)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*var;
// 	t_list	*ret;

// 	i = 0;
// 	while (check_char(str[i]))
// 	{
// 		if (str[i] == '$')
// 		{
// 			tmp = ft_substr(str, 0, i, trash); 
// 			j = 1;
// 			while (check_char(str[i + j]))
// 				j++;
// 			var = ft_substr(str, i, j, trash);
// 			ret = find_var_env(env, var, 0);
// 			if (!ret)
// 				return (tmp);
// 			else
// 				tmp = ft_strjoin(tmp, ret->valeur, trash);
// 		}
// 		i++;
// 	}
// 	return (tmp);
// }

// char	*ft_word(char *str, t_shell *info)
// {
// 	int		i;
// 	int		check;
// 	char	*tmp;

// 	i = 0;
// 	check = 0;
// 	tmp = NULL;
// 	if (info->token && is_here_doc(info->token))
// 	{
// 		while (!ft_isparsing_char(str[i]))
// 			i++;
// 		creat_and_add(tmp, str, WORD, i, info);
// 	}
// 	else
// 	{
// 		while (!ft_isparsing_char(str[i]))
// 		{
// 			if (str[i] == '$' && check == 0)
// 		{
// 			tmp = ft_word_d(str, info->env, &info->trash_lst);
// 			check++;
// 		}
// 			else if (str[i] == '$' && check != 0)
// 				tmp = ft_word_d(tmp, info->env, &info->trash_lst);

// 			i++;
// 		}
// 		creat_and_add(tmp, str, WORD, i, info);
// 	}
// 	return (str + i);
// }
