#include "minishell.h"

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
		buffer = readline("> ");
    heredoc_lst = ft_lstnew_heredoc(buffer, trash);
	heredoc_lst = heredoc_lst->next;
    while(ft_strncmp(buffer, to_check, (ft_strlen(to_check) + 1)) != 0)
    {
        node = ft_lstnew_heredoc(buffer, trash);
        ft_lstadd_front(&heredoc_lst, node);
        buffer = readline("> ");
    }
    res = create_tab(&heredoc_lst, trash);
    return(res);
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