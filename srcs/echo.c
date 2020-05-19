/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <ylegzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:46:20 by ylegzoul          #+#    #+#             */
/*   Updated: 2020/05/19 13:47:32 by ylegzoul         ###   ########.fr       */
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
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] && input[i + 1] &&
		input[i] == '-' && input[i + 1] == 'n')
	{
		opt = 1;
		if (input[i + 2] && input[i + 2] == ' ')
			i += 3;
		else if (!input[i + 2])
			return (0);
		else if (input[i + 2])
			opt = 0;
	}
	while (input[i])
	{
		i--;
		if (input[++i] == quote)
			quote = 0;
		else if (quote == 0 && (input[i] == '"' || input[i] == 39))
			if (i == 0 || input[i - 1] != 92)
			{
				quote = input[i];
				i++;
			}
		if (quote == 0 && (input[i] == '>' || input[i] == '<'))
			return (1);
		else if (quote != 0 || input[i] != ' ' || (input[i - 1] != ' '))
			*result = ft_add_char(*result, input[i]);
		i++;
	}
	if (i > 0 && opt == 0)
		ft_print(*result, ft_strlen(*result), cmd, 1);
	else if (i > 0 && opt != 0)
		ft_print(*result, ft_strlen(*result), cmd, 0);
	else if (opt == 0)
		ft_print("\n", 1, cmd, 0);
	g_data->ret = 0;
	return (0);
}

int			echo(char *input, char **result, t_cmd *cmd)
{
	int		i;
	int		j;
	int		fd[OPEN_MAX];

	i = 0;
	ft_init_tab(fd, OPEN_MAX);
	if (ft_parse_echo(input, fd, result, cmd))
		return (1);
	return (0);
}
