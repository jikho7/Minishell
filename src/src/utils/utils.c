#include "../../minishell.h"

/* ---------------------- 1.Recherche de char ----------------------------*/
int	found_char(const char *str, int c)
{
	char	*cpy_str;
	int		i;

	cpy_str = (char *)str;
	i = 0;
	while (*cpy_str)
	{
		if (*cpy_str == c)
			i++;
		cpy_str++;
	}
	return (i);
}

/* ---------------------- 2.Swap ptr str ----------------------------*/
void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

/* ---------------------- 3.Taille tableau ----------------------------*/
int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/* ---------------------- 4.Initialisation ----------------------------*/
void	init_shell(t_shell *info, char **envp)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (getcwd(info->cwd, 1024) == NULL)
	{
		ft_putendl_fd("getcwd() error", 2);
		g_errno = 1;
	}
	info->trash_lst = ft_calloc(1, sizeof(t_dlist));
	info->env = ft_dlst_new(&info->trash_lst);
	tab_to_lst(info, envp);
	info->status = 0;
}
