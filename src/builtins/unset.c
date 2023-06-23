#include "../../minishell.h"

static void	clear_node(t_shell **info, t_list *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
	node->valeur = NULL;
	node->variable = NULL;
	free(node->valeur);
	free(node->variable);
	free(node);
	(*info)->env->len--;
}

void	unset_minishell(t_shell **info)
{
	t_list	*node;
	int		i;

	i = 1;
	if ((*info)->arg)
	{
		while ((*info)->arg[i])
		{
			node = find_var_env((*info)->env, (*info)->arg[i], 0);
			if (node != NULL && strncmp(node->data, "not_found", 10) != 0)
				clear_node(info, node);
		}
	}
}
