#include "../../minishell.h"

char	*red_in(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	if (ft_strncmp(str, "<<", 2) == 0)
	{
		token = new_node(ft_strdup("<<", trash), HERE_DOC, trash);
		tok_addlst(lst, token);
		return (str + 2);
	}
	else
	{
		token = new_node(ft_strdup("<", trash), RED_IN, trash);
		tok_addlst(lst, token);
		return (str + 1);
	}
}

char	*red_out(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	if (ft_strncmp(str, ">>", 2) == 0)
	{
		token = new_node(ft_strdup(">>", trash), APPEND, trash);
		tok_addlst(lst, token);
		return (str + 2);
	}
	else
	{
		token = new_node(ft_strdup(">", trash), RED_OUT, trash);
		tok_addlst(lst, token);
		return (str + 1);
	}
}
