/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:55:36 by acoudouy          #+#    #+#             */
/*   Updated: 2020/05/28 16:05:12 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void		print_cmd_not_found(t_cmd *cmd)
{
	if (cmd->exept_case)
		return ;
	g_data->ret = 127;
	write(2, "minishell: ", 11);
	ft_putnbr_fd(cmd->nb_cmd, 2);
	write(2, ": ", 2);
	write(2, g_data->cmd_n_found, ft_strlen(g_data->cmd_n_found));
	if (cmd->arg && cmd->arg[0] != 0)
	{
		write(2, " ", 1);
		write(2, cmd->arg, ft_strlen(cmd->arg));
	}
	write(2, ": not found\n", 12);
}

int			print_cd_error(char *s)
{
	write(2, "minishell: ", 11);
	ft_putnbr_fd(g_data->step_cmd, 2);
	write(2, ": cd: can't cd to ", 18);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	g_data->ret = 2;
	return (1);
}

int			print_error_unexpected(char c)
{
	g_data->step_cmd++;
	write(2, "minishell: ", 11);
	ft_putnbr_fd(g_data->step_cmd, 2);
	write(2, ": Synthax error: '", 18);
	write(2, &c, 1);
	write(2, "' unexpected\n", 13);
	g_data->ret = 2;
	return (1);
}

int			print_error_nl_expected(void)
{
	g_data->step_cmd++;
	write(2, "minishell: ", 11);
	ft_putnbr_fd(g_data->step_cmd, 2);
	write(2, ": Synthax error: newline expected\n", 35);
	g_data->ret = 2;
	return (1);
}

int			n_inside_q(char *s, int i)
{
	int		j;
	int		k;
	char	c;

	j = 0;
	while (s[j] && s[j] != '"' && s[j] != 39)
		j++;
	k = j;
	if (s[j])
		c = s[j];
	while (s[k] && s[k] != c)
		k++;
	if (s[k] && j < i && k > i)
		return (1);
	return (0);
}

int			check_error_unexpected(char *s)
{
	int		i;

	i = -1;
	if (s[0] && (s[0] == '|' || s[0] == ';'))
		return (print_error_unexpected(s[0]));
	if (s[0] && s[0] == '<')
		return (print_error_unexpected(s[0]));
	while (s[++i])
	{
		if ((s[i] == '|' || s[i] == ';') && s[i + 1])
		{
			i++;
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 1)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 1)
				return (print_error_nl_expected());
			while (s[i] && s[i] == ' ')
				i++;
			if (s[i] && (s[i] == '|' || s[i] == ';') && n_inside_q(s, i) == 1)
				return (print_error_unexpected(s[i]));
			if (s[i] && (s[i] == '<' || s[i] == '>') && n_inside_q(s, i) == 1)
				return (print_error_nl_expected());
		}
	}
	return (0);
}

int			check_red(char *line)
{
	int		i;

	i = ft_strlen(line);
	if (i > 0)
	{
		if (line[i - 1] == '<' || line[i - 1] == '>')
			return (print_error_nl_expected());
	}
	return (0);
}
