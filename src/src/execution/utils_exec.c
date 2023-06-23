#include "minishell.h"

char	*strjoin_exec(char const *s1, char const *s2)
{
	char	*cs1;
	char	*cs2;
	char	*result;
	int		i;
	int		j;

	cs1 = (char *)s1;
	cs2 = (char *)s2;
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ((ft_strlen(cs1)) + (ft_strlen(cs2)) + 1));
	if (result == NULL)
		return (NULL);
	while (cs1[i])
		result[j++] = cs1[i++];
	result[j] = ' ';
	i = 0;
	while (cs2[i])
		result[j++] = cs2[i++];
	result[j] = '\0';
	return (result);
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
