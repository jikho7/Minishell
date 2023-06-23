#include "../../minishell.h"

static void	strjoin_node(t_tok *dest, t_tok *src, t_dlist **trash)
{
	dest->tok = ft_strjoin(dest->tok, src->tok, trash);
	dest->next = src->next;
	src->next = NULL;
}

int	check_syntax(t_tok *lst, t_dlist **trash)
{
	int		i;
	int		in;
	char	*input;
	t_tok	*node;
	t_tok	*ptr_tmp;

	i = 0;
	node = lst;
	in = 0;
	// print_token(&lst, "Synatx");
	while (node != NULL)
	{
		if (node->type == RED_IN || node->type == RED_OUT
			|| node->type == HERE_DOC || node->type == APPEND)
		{
			ptr_tmp = node->next;
			if (!ptr_tmp)
				return (ft_error_msg(258, NULL));
			if (ptr_tmp->type == SPACE)
				ptr_tmp = ptr_tmp->next;
			if (!ptr_tmp)
				return (ft_error_msg(258, NULL));
			else if (ptr_tmp->type != WORD)
				return (ft_error_msg(258, ptr_tmp->tok));
			if (node->type == RED_IN && ptr_tmp->type == WORD)
			{
				in = open(ptr_tmp->tok, O_RDONLY);
				input = ptr_tmp->tok;
			}
			node = node->next;
		}
		else if (node->type == PIPE && i == 0)
			return (ft_error_msg(258, node->tok));
		else if ((node->type == WORD || node->type == D_QUOTE)
					&& node->next != NULL)
		{
			if (node->next->type == WORD || node->next->type == D_QUOTE)
				strjoin_node(node, node->next, trash);
			else
				node = node->next;
		}
		else
			node = node->next;
		i++;
	}
	if (in < 0)
		return (ft_error_msg(1, input));
	return (0);
}

// if node_type == SPACE
// 	s++;
// else if node_type == RED_IN
// 	while (node_type == SPACE)
// 		if (node_type == NULL) /* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s
// 	else (node_type == WORD)
// 		in = open(s, O_RDONLY)
// 		if (in < 0)
// 			return (2) -->> bash: salut: No such file or directory

// else if node_type == HERE_DOC
// 	while (node_type == SPACE)
// 		if (node_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_type == RED_OUT
// 	while (node_type == SPACE)
// 		if (node_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_type == APPEND
// 	while (node_type == SPACE)
// 		if (node_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_type == PIPE
// 	if PIPE == first_node
// 		return (1) -->> bash: syntax error near unexpected token `|
