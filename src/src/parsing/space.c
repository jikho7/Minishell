#include "../../minishell.h"

char	*ft_space(char *str, t_tok **lst, t_dlist **trash)
{
	int		i;
	t_tok	*token;

	i = 0;
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	token = new_node(ft_strdup(" ", trash), SPACE, trash);
	tok_addlst(lst, token);
	return (str + i);
}
