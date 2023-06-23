#include "../../minishell.h"

void	pwd_minishell(t_shell *info)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (getcwd(info->cwd, sizeof(info->cwd)) != NULL)
		printf("%s\n", info->cwd);
	else
	{
		ft_putendl_fd("getcwd() error", 2);
		g_errno = 1;
	}
}

// int	main(void)
// {
	// t_mshl	info;
// 
	// pwd_minishell(&info);
	// return (0);
// }
// 