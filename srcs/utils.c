#include "../inc/minishell.h"

int					size_int(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n /10;
		i++;
	}
	return (i);
}
	
int					power_of_ten(int n)
{
	int 	i;

	i = 1;
	while (n > 0)
	{
		i = i * 10;
		n--;
	}
	return (i);
}

int 		check_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (i < ft_strlen(s))
		return (1);
	return (0);
}
