/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 20:14:19 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/01 20:16:25 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char				*env_question_found(char **line)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = -1;
	j = 0;
	size = size_int(g_data->ret) + 1;
	if (!(ret = malloc(sizeof(char) * ft_strlen(*line) + (size - 1) - 1)))
		return (0);
	ret[ft_strlen(*line) + (size - 1) - 2] = '\0';
	while ((*line)[++i] && (*line)[i] != '$')
		ret[i] = (*line)[i];
	while (--size > 0)
	{
		ret[i + j] = (g_data->ret / power_of_ten(size - 1)) + '0';
		g_data->ret = g_data->ret % power_of_ten(size - 1);
		j++;
	}
	i--;
	while ((*line)[++i + 2])
		ret[i + j] = (*line)[i + 2];
	free(*line);
	return (ret);
}

int					check_space_after_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (line[i] && (line[i + 1] == 0 || line[i + 1] == ' '))
		return (1);
	return (0);
}
