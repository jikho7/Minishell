#include "minishell.h"

int	ft_lstsize_heredoc(t_list *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*ft_strcat_heredoc(char *dest, char *src, int end)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i++] = src[j++];
	}
	if (end == 0)
		dest[i] = ' ';
	if (end == 1)
		dest[i] = '\0';
	return (dest);
}

t_list	*ft_lstnew_heredoc(char *data, t_dlist **trash_lst)
{
	t_list	*list;
    size_t size;

    size = ft_strlen(data);
	list = my_malloc(1, sizeof(t_list), trash_lst);
    list->valeur = my_malloc((size + 1), sizeof(char*), trash_lst);
	if (list->valeur == NULL)
		return (NULL);
	if (!list)
		return (NULL);
	list->valeur = ft_strcpy(list->valeur, data);
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back_heredoc(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast(*lst);
	ptr->next = new;
}