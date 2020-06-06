/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:59:55 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/06 10:31:54 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data		*g_data;

int			main(int ac, char **av, char **environ)
{
	t_data	data;
	int		exit_status;

	if (ac != 1)
	{
		write(1, "Error: nb argument invalid.\n", 28);
		write(1, "Must be zero.\n", 14);
		return (1);
	}
	g_data = &data;
	ft_init_data(&data);
	ft_init_env(data.lst_env, environ);
	ft_start(&data);
	exit_status = g_data->ret;
	free_data();
	return (exit_status);
}

int			ft_start(t_data *data)
{
	char	*line;
	int		ex;

	ex = 0;
	while (data->exit == 0)
	{
		data->exit = 0;
		while (data->exit == 0)
		{
			signal(SIGINT, signal_prevent);
			signal(SIGQUIT, signal_prevent);
			ft_print_prompt();
			if (get_next_line(0, &line) == 0)
				ex = 1;
			ft_lstadd_front_hist(data, line);
			if (check_error_unexpected(line) == 0 && check_red(line) == 0)
				ft_exec_line(data);
			ft_exit_d(ex, line);
			free(line);
		}
	}
	return (0);
}

void		ft_print_prompt(void)
{
	write(1, "minishell$> ", 12);
}

void		ft_exit(t_cmd *cmd)
{
	int		exit_status;
	int		i;

	i = 0;
	exit_status = g_data->ret;
	if (cmd->arg && cmd->arg[0] != 0)
		exit_status = ft_atoi(cmd->arg) % 256;
	while (cmd->arg && cmd->arg[i])
	{
		if (ft_isdigit(cmd->arg[i]) != 1)
			exit_status = -100;
		i++;
	}
	if (exit_status < 0 && cmd->cmd == EXIT)
	{
		write(2, "minishell: ", 11);
		ft_putnbr_fd(cmd->nb_cmd, 2);
		write(2, ": exit : Illegal number: ", 25);
		write(2, cmd->arg, ft_strlen(cmd->arg));
		write(2, "\n", 1);
		g_data->ret = 2;
		return ;
	}
	g_data->ret = exit_status % 256;
	g_data->exit = 1;
}

void		ft_exit_d(int ex, char *line)
{
	if (ex)
	{
		if (line[0] != 0)
			ft_print_prompt();
		g_data->exit = 1;
	}
}
