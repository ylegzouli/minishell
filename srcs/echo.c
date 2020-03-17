#include "../inc/minishell.h"

int			ft_add_fd(int *fd, char *input, int *i)
{
	int		j;
	char	*path;
//	int		flag;

	j = 0;
	path = 0;
	while (j < OPEN_MAX && fd[j] != 0)
		j++;
	*i += 1;
//	flag = 00000100;
	if (input[*i] == input[*i - 1])
	{
//		flag = 00000002;
		*i += 1;
	}
	while (input[*i] == ' ')
		*i += 1;
	while (input[*i] && input[*i] != ' ')
	{
		path = ft_add_char(path, input[*i]);
		*i += 1;
	}
//	if ((fd[j] = open(path, flag)) == -1)
	if ((fd[j] = open(path, O_CREAT | O_RDWR | O_APPEND )) == -1)
		return (1);
	return (0);
}

int			ft_parse_echo(char *input, int *fd, char **result)
{
	int		i;
	int		opt;

	i = 0;
	opt = 0;
//	if (input[0] == '-' && input[0] == 'n' && input[0] == ' ')
//	{
//		i = 3;
//		opt = 1;
//	}
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (ft_add_fd(fd, input, &i))
				return (1);
		}
		else
			*result = ft_add_char(*result, input[i]);
		i++;
	}
//if opt
	*result = ft_add_char(*result, '\n');
	return (0);
}

int			echo(char *input, char *result)
{
	int		i;
	int		j;
	int		fd[OPEN_MAX];

	i = 0;
	ft_init_tab(fd, OPEN_MAX);
	if (ft_parse_echo(input, fd, &result))
		return (1);
	while (i == 0 || fd[i] != 0)
	{
		printf("fd = %d\n", fd[i]);
		j = 0;
		while (result[j])
		{
			write(fd[i], &result[j], 1);
			j++;
		}	
		i++;
	}
	return (0);
}
