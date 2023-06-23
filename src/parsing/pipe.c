#include "../../minishell.h"

char	*ft_pipe(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	token = new_node(ft_strdup("|", trash), PIPE, trash);
	tok_addlst(lst, token);
	return (str + 1);
}
