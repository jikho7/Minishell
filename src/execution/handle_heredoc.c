#include "minishell.h"
char    **heredoc_data_saved(char *to_check, t_exec *exe, char *buffer);
void	display_lst(t_list **ptr_to_head, char *name);
void	display_node(t_list *lst);
char    *ft_strcpy(char *s1, char *s2);
t_list	*ft_lstnew_heredoc(char *data, t_dlist **trash_lst);
char	**create_tab(t_list **lst, t_dlist **trash);
int		ft_lstsize_heredoc(t_list *lst);
int		convert_tab_to_fd_heredoc(char **heredoc_res);
char	*create_str_heredoc(char **exe_heredoc, t_exec *exe);
char	*ft_strcat_heredoc(char *dest, char *src, int end);
int		is_tab_heredoc_empty(char **tab);

char *create_str_heredoc(char **exe_heredoc, t_exec *exe)
{
	char *result;
	int i;

	i = 0;
	result = my_malloc(100, sizeof(char*), exe->trash_lst_exe);
	while(exe_heredoc[i])
	{
		if (!exe_heredoc[i + 1])
			result = ft_strcat_heredoc(result, exe_heredoc[i], 1);
		else
			result = ft_strcat_heredoc(result, exe_heredoc[i], 0);
		i++;
	}
	return (result);
}

int is_tab_heredoc_empty(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp((const char*)tab[i], "") != 0)
			return (0);
		i++;
	}
	return (1);
}

int handle_heredoc(t_exec *d_exe)
{
    int		i;
    int		size;
    char	*buffer = NULL;
	char	**heredoc_tab;
	char	**heredoc_res = NULL;

	i = 0;
	if (is_tab_heredoc_empty(d_exe->heredoc) == 1)
	{
		d_exe->str_heredoc = my_malloc(1, sizeof(char*), d_exe->trash_lst_exe);
		d_exe->str_heredoc = "";
		return (0);
	}
	d_exe->str_heredoc = create_str_heredoc(d_exe->heredoc, d_exe);
	//fprintf(stderr, "ft_handle_heredoc %s\n", d_exe->str_heredoc);
	heredoc_tab = ft_split_exec(d_exe->str_heredoc, ' ', 0);
    size = ft_tabsize(heredoc_tab);//size_tab = ft_tabsize(d_exe->heredoc);
    while(heredoc_tab[i])
    { 
        if (i == size - 1)
		{	
            heredoc_res = heredoc_data_saved(heredoc_tab[i], d_exe, buffer);
			break;
		}
		if (buffer)
		{
        	if (ft_strncmp(buffer, heredoc_tab[i], (ft_strlen(heredoc_tab[i]) + 1)) == 0)
           		i++;
		}
        buffer = readline("");
    }
	i = convert_tab_to_fd_heredoc(heredoc_res);
	return (i);
}

int convert_tab_to_fd_heredoc(char **heredoc_res)
{
	int size;
	int j;
	int fd;

	fd = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
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

char **heredoc_data_saved(char *to_check, t_exec *d_exe, char *buffer)
{
    (void)d_exe;
   // fprintf(stderr, ">>position heredoc: %s\n", to_check);
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
        ft_lstadd_front(&heredoc_lst, node);
        buffer = readline("");
    }
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


// void	display_lst(t_list **ptr_to_head, char *name)
// {
// 	t_list	*current_node;
// 	int		count;

// 	current_node = *ptr_to_head;
// 	count = 0;
// 	printf("\n%s :\n", name);
// 	if (*ptr_to_head != NULL)
// 	{
// 		while (current_node->next != NULL)
// 		{
// 			printf("Index = %d : ", count);
// 			display_node(current_node);
// 			current_node = current_node->next;
// 			count++;
// 		}
// 		printf("Index = %d : ", count);
// 		display_node(current_node);
// 	}
// 	else
// 		printf("The stack is empty.\n");
// 	printf("\n");
// }

// void	display_node(t_list *lst)
// {
// 	if (lst != NULL)
// 	{
// 		printf("[%p] {value = %s | nx = %p}\n", lst,
// 			lst->valeur,
// 			lst->next);
// 	}
// }

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
	size = ft_lstsize_heredoc(*lst);
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