/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudouy <acoudouy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:59:55 by acoudouy          #+#    #+#             */
/*   Updated: 2020/05/28 11:00:23 by acoudouy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data		*g_data;

int			main(void)
{
	t_data	data;

	g_data = &data;
	ft_init_data(&data);
	ft_init_env(data.lst_env);
	ft_start(&data);
	return (0);
}

int			ft_start(t_data *data)
{
	char *line;

	while (data->exit == 0)
	{
		data->exit = 0;
		while (data->exit == 0)
		{
			signal(SIGINT, signal_prevent);
			signal(SIGQUIT, signal_prevent);
			ft_print_prompt();
			get_next_line(0, &line);
			ft_lstadd_front_hist(data, line);
			if (check_error_unexpected(line) == 0 && check_red(line) == 0)
				ft_exec_line(data);
			free(line);
		}
	}
	return (0);
}

void		ft_print_prompt(void)
{
	write(1, "minishell$> ", 12);
}
