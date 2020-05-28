/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:46:20 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/28 14:53:33 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			ft_parse_echo(char *input, int *fd, char **result, t_cmd *cmd)
{
	int		i;
	int		opt;
	char	quote;

	i = 0;
	opt = 0;
	quote = 0;
	while (input[i] && input[i + 1] && input[i] == '-' && input[i + 1] == 'n')
	{
		opt = 1;
		if (input[i + 2] && input[i + 2] == ' ')
			i += 3;
		else if (!input[i + 2])
			return (0);
		else if (input[i + 2])
			opt = 0;
	}
	*result = ft_strdup(input + i);
	printer(i, result, cmd, opt);
	return (0);
}

void		printer(int i, char **result, t_cmd *cmd, int opt)
{
	if (opt == 0)
		ft_print(*result, ft_strlen(*result), cmd, 1);
	else if (opt != 0)
		ft_print(*result, ft_strlen(*result), cmd, 0);
	g_data->ret = 0;
}

int			echo(char *input, char **result, t_cmd *cmd)
{
	int		i;
	int		j;
	int		fd[1];

	i = 0;
	if (input[0] == 0)
	{
		ft_print("", 0, cmd, 2);
		return (0);
	}
	if (ft_parse_echo(input, fd, result, cmd))
		return (1);
	return (0);
}
