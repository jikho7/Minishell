/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:04:23 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/29 14:51:32 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tok	*new_node(char *str, int token, t_dlist **trash)
{
	t_tok	*new;

	new = my_malloc(1, sizeof(t_tok), trash);
	if (!new)
		return (NULL);
	new->tok = str;
	new->type = token;
	new->next = 0;
	return (new);
}

void	tok_addlst(t_tok **lst, t_tok *token)
{
	t_tok	*ptr;

	ptr = *lst;
	if (!token)
		return ;
	if (!*lst)
	{
		*lst = token;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = token;
}

void	tok_clearlst(t_tok **lst)
{
	t_tok	*ptr;

	if (!*lst)
		return ;
	ptr = *lst;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free((*lst)->tok);
		free(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}