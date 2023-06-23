#include "../../minishell.h"

/* ------------------------- cd sans option ------------------------------*/
static void	go_home(t_shell *info)
{
	char	**path_home;
	char	*path_home_2;
	int		i;

	path_home = ft_split(info->cwd, '/', &info->trash_lst);
	i = 0;
	while (path_home[i])
		i++;
	path_home_2 = ("..");
	while (i-- > 2)
		path_home_2 = ft_strjoin(path_home_2, "/..", &info->trash_lst);
	chdir(path_home_2);
	getcwd(info->cwd, 1024);
}

/* ---------------------------- fonction cd ---------------------------------*/
void	cd_minishell(t_shell *info)
{
	int		ret;

	if (!*info->arg)
		go_home(info);
	else
	{
		ret = chdir(*info->arg);
		if (ret == -1)
			ft_error_msg(1, *info->arg);
		else
			getcwd(info->cwd, 1024);
	}
}
