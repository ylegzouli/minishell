#include "../inc/minishell.h"

char *ft_strrstr_without(char *str, char *to_find)
{
	int i;
	int j;
	int	lastpos;

	i = 0;
	lastpos = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
				lastpost = i;
			j++;
		}
		i++;
	}
	if (lastpost > 0)
		return (str + lastpos + ft_strlen(to_find));
	return (str);
}
