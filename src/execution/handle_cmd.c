#include "minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_exec *info, t_dlist **trash)
{
	int		i;
	char	*cmd_path;
	(void)trash;
	i = 0;
	while (info->access_path[i])
	{
		cmd_path = strjoin_exec(info->access_path[i], cmd);
		if (access (cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		else
		i++;
	}
	//fprintf(stderr, "ft_get_command path; %s\n", cmd);
	command_not_found(cmd);
	exit(1);
	return (NULL);
}
