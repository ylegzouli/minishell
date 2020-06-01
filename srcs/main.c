/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:59:55 by acoudouy          #+#    #+#             */
/*   Updated: 2020/06/01 20:23:25 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data		*g_data;

int			main(int ac, char **av, char **environ)
{
	t_data	data;

	g_data = &data;
	ft_init_data(&data);
	ft_init_env(data.lst_env, environ);
	ft_start(&data);
	return (0);
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
			free(line);
			if (ex)
			{
				ft_print_prompt();
				ft_exit();
			}
		}
	}
	return (0);
}

void		ft_print_prompt(void)
{
	write(1, "minishell$> ", 12);
}

void		ft_exit(void)
{
	free_data();
	g_data->exit = 1;
}
