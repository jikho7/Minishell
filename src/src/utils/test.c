#include "../../minishell.h"

void	print_tab(char **tab, char *ft)
{
	int	i;

	i = 0;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("----------------------------------------------------------------\n");
}

void	print_list(t_env *lst, char *ft)
{
	t_list	*node;

	node = lst->head;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	printf("%zu\n", lst->len);
	while (node != NULL)
	{
		printf("Data:		%p\n", node->data);
		printf("Variable:	%s\n", node->variable);
		printf("Valeur:		%s\n", node->valeur);
		node = node->next;
	}
	printf("----------------------------------------------------------------\n");
}

void	print_token(t_tok **lst, char *ft)
{
	t_tok	*node;

	node = *lst;
	printf("%s\n", ft);
	printf("|----------------------------|\n");
	while (node != NULL)
	{
		printf(" Token:	%s, Type:	%u, next_ptr:	%p\n", node->tok, node->type, node->next);
		if (node->next != NULL)
			printf("|----------------------------|\n");
		node = node->next;
	}
	printf("|----------------------------|\n");
}

void	test(char *str, char *fonction)
{
	static int	i;

	printf("---->> %s\n", fonction);
	printf("%d.%s\n", i, str);
	i++;
}