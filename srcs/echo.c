#include "../inc/minishell.h"
/*
int			ft_add_fd(int *fd, char *input, int *i)
{
	int		j;
	char	*path;
	int		flag;

	j = 0;
	path = 0;
	flag = 0;
	while (j < OPEN_MAX && fd[j] != 0)
		j++;
	*i += 1;
	if (input[*i] == input[*i - 1])
	{
		flag = 1;
		*i += 1;
	}
	while (input[*i] == ' ')
		*i += 1;
	while (input[*i] && input[*i] != ' ')
	{
		path = ft_add_char(path, input[*i]);
		*i += 1;
	}
	if (flag == 0)
		if ((fd[j] = open(path, O_CREAT | O_RDWR | O_TRUNC)) == -1)
			return (1);	
	if (flag == 1)
		if ((fd[j] = open(path, O_CREAT | O_RDWR | O_APPEND)) == -1)
			return (1);	
	return (0);
}
*/
int			ft_parse_echo(char *input, int *fd, char **result)
{
	int		i;
	int		opt;
	char	quote;

	i = 0;
	opt = 0;
	quote = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] && input[i + 1] && input[i + 2] &&
		input[i] == '-' && input[i + 1] == 'n' && input[i + 2] == ' ')
	{
		i += 3;
		opt = 1;
	}
	while (input[i])
	{
		if (input[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (quote == 0 && (input[i] == '"' || input[i] == 39))
			if (i == 0 || input[i - 1] != 92)
			{
				quote = input[i];
				i++;
			}
		if (quote == 0 && (input[i] == '>' || input[i] == '<'))
		{
		//	if (ft_add_fd(fd, input, &i))
				return (1);
		}
		else if (quote != 0 || input[i] != ' ' || (input[i - 1] != ' '))
			*result = ft_add_char(*result, input[i]);
		i++;
	}
	if (opt == 0)
		*result = ft_add_char(*result, '\n');
//	printf("|%s|\n", *result);
	return (0);
}

int			echo(char *input, char **result)
{
	int		i;
	int		j;
	int		fd[OPEN_MAX];

	i = 0;
	ft_init_tab(fd, OPEN_MAX);
	if (ft_parse_echo(input, fd, result))
		return (1);
/*	while (i == 0 || fd[i] != 0)
	{
		j = 0;
		while (result[j])
		{
			write(fd[i], &result[j], 1);
			j++;
		}
		if (fd[i] != 0)
			close(fd[i]);
		i++;
	}*/
	return (0);
}
