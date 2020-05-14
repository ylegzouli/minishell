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

int			size_var_env_not_found(char *line)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (line[i] && line[i] != '$')
		i++;
	i++;
	while (line[i + size] &&
		(line[i + size] != ' ' && line[i + size] != '$'))
		size++;
	return (size);
}

int			check_var_env_return(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?')
				return (1);
		}
		i++;
	}
	return (0);
}
