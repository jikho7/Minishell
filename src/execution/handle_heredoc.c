#include "minishell.h"
void    heredoc_display(t_exec *d_exe);
char    **here_doc_data_saved(char *to_check, t_exec *exe, char *buffer);
void	display_lst(t_list **ptr_to_head, char *name);
void	display_node(t_list *lst);
char    *ft_strcpy(char *s1, char *s2);
char	**lst_to_tab_heredoc(t_list *lst, t_dlist **trash);
t_list	*ft_lstnew_heredoc(char *data, t_dlist **trash_lst);
char	**create_tab(t_list **lst, t_dlist **trash);
int	ft_lstsize_here(t_list *lst);
int convert_tab_to_fd_herdoc(char **heredoc_res);


int handle_heredoc(t_exec *d_exe, t_pipe *d_pip)
{
    int i;
    int size_tab;
    char *buffer = NULL;
	char	**heredoc_res = NULL;
    (void)d_exe;
	(void)d_pip;
    
    size_tab = ft_tabsize(d_exe->heredoc);
    i = 0;
    while(d_exe->heredoc[i])
    { 
        if (i == size_tab - 1)
		{	
			//buffer = readline("");
			fprintf(stderr, "plop\n");
            heredoc_res = here_doc_data_saved(d_exe->heredoc[i], d_exe, buffer);
			break;
		}
		if (buffer)
		{
        	if (ft_strncmp(buffer, d_exe->heredoc[i], (ft_strlen(d_exe->heredoc[i]) + 1)) == 0)
           		i++;
		}
        buffer = readline("");
    }
	i = 0;
	// while(heredoc_res[i])
	// {
	// 	fprintf(stderr, "%s\n", heredoc_res[i]);
	// 	i++;
	// }
	// i = 0;
	i = convert_tab_to_fd_herdoc(heredoc_res);
   // d_pip->fd_in = i;
	return (i);
}

int convert_tab_to_fd_herdoc(char **heredoc_res)
{
	int size;
	int j;
	int fd = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		fprintf(stderr, "error fd heredoc\n");
		return (0);
	}
	size = ft_tabsize(heredoc_res);
	while((size - 1) >= 0)
	{
		j = 0;
		while(heredoc_res[size - 1][j])
		{
			write(fd, &heredoc_res[size - 1][j], 1);
			j++;
		}
		write(fd, "\n", 1);
		size--;
	}
	close(fd);
	return (fd);
}

char **here_doc_data_saved(char *to_check, t_exec *d_exe, char *buffer)
{
    (void)d_exe;
    fprintf(stderr, ">>position heredoc: %s\n", to_check);
    char **res;
    res = NULL;
    t_dlist **trash = NULL;
    t_list *heredoc_lst = NULL;
    t_list *node = NULL;
	if (!buffer)
		buffer = readline("");
    heredoc_lst = ft_lstnew_heredoc(buffer, trash);
	heredoc_lst = heredoc_lst->next;
    while(ft_strncmp(buffer, to_check, (ft_strlen(to_check) + 1)) != 0)
    {
        node = ft_lstnew_heredoc(buffer, trash);
       // display_node(node);
        ft_lstadd_front(&heredoc_lst, node);
       // display_lst(&heredoc_lst, "here");
        buffer = readline("");
    }
   //	display_lst(&heredoc_lst, "plopp");
    res = create_tab(&heredoc_lst, trash);
    return(res);
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


void	display_lst(t_list **ptr_to_head, char *name)
{
	t_list	*current_node;
	int		count;

	current_node = *ptr_to_head;
	count = 0;
	printf("\n%s :\n", name);
	if (*ptr_to_head != NULL)
	{
		while (current_node->next != NULL)
		{
			printf("Index = %d : ", count);
			display_node(current_node);
			current_node = current_node->next;
			count++;
		}
		printf("Index = %d : ", count);
		display_node(current_node);
	}
	else
		printf("The stack is empty.\n");
	printf("\n");
}

void	display_node(t_list *lst)
{
	if (lst != NULL)
	{
		printf("[%p] {value = %s | nx = %p}\n", lst,
			lst->valeur,
			lst->next);
	}
}

char    *ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
    if(!s2)
        return(NULL);
    while(s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return(s2);
}


char	**create_tab(t_list **lst, t_dlist **trash)
{
	(void)trash;
	t_list	*tmp;
	char	**tab;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_here(*lst);
	//tab = (char**)malloc(sizeof(char*) * (size));
	tab = my_malloc(size, sizeof(char**),  trash);
	if (tab == NULL)
		return (NULL);
	tmp = *lst;
	while (i < size - 1)
	{
		tab[i] = tmp->valeur;
		tmp = tmp->next;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

int	ft_lstsize_here(t_list *lst)
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