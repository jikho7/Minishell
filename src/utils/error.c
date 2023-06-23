#include "../../minishell.h"

// static void	ft_other_error(int errno, char *str)
// {

// }

int	ft_error_msg(int errno, char *str)
{
	int g_errno = 0;
	fprintf(stderr, "%d", g_errno);
	if (errno == 1 && str == NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_errno = 1;
	}
	if (errno == 1)
	{
		printf("bash: %s: No such file or directory\n", str);
		g_errno = errno;
	}
	else if (errno == 126)
	{
		printf("env: %s: Premission denied\n", str);
		g_errno = errno;
	}
	else if (errno == 127 && str == NULL)
	{
		printf("env: %d: No such file or directory\n", g_errno);
		g_errno = errno;
	}
	else if (errno == 127 && str != NULL)
	{
		printf("env: %s: No such file or directory\n", str);
		g_errno = errno;
	}
	else if (errno == 258 && str == NULL)
	{
		printf("bash: syntax error near unexpected token `newline\'\n");
		g_errno = errno;
	}
	else if (errno == 258)
	{
		printf("bash: syntax error near unexpected token `%s\'\n", str);
		g_errno = errno;
	}
	// else
	// 	ft_other_error(errno, str);
	return (1);
}