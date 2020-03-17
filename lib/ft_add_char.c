#include "../inc/minishell.h"

char *ft_add_char(char *str, char c)
{
	size_t len = 0;
	if (str)
		len = strlen(str);
	char *tmp = malloc(len + 2);
	int i = 0;
	while (str && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len] = c;
	tmp[len + 1] = 0;
	if (str)
		free(str);
	return (tmp);
}
