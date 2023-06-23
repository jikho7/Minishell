#include "minishell.h"

// t_list	*create_lst_exec(int ac, char **av)
// {
// 	int		i;
// 	t_list	*tmp;
// 	t_list	*stack_a;

// 	i = 1;
// 	stack_a = NULL;
// 	if (ac > 2)
// 	{
// 		stack_a = ft_lstnew(av[0], NULL);
// 		while (i < ac)
// 		{
// 			tmp = ft_lstnew(av[i],NULL);
// 			ft_lstadd_back(&stack_a, tmp);
// 			i++;
// 		}
// 	}
// 	return (stack_a);
// }

// void	print_list_exec(t_list *lst, char *ft)
// {
// 	t_list	*node;

// 	node = lst;
// 	printf("%s\n", ft);
// 	printf("----------------------------------------------------------------\n");
// 	while (node != NULL)
// 	{
// 		printf("%s", node->data);
// 		printf("\n");
// 		node = node->next;
// 	}
// 	printf("----------------------------------------------------------------\n");
// }

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
