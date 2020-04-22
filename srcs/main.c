#include "../inc/minishell.h"

t_data          *g_data;

int		main()
{
	t_data	data;

	g_data = &data;
	ft_init_data(&data);
	ft_init_env(data.lst_env);
	ft_start(&data);
	//ft_free_data(&data);
	return (0);
}

int		ft_start(t_data *data)
{
	char *line;

	while(data->exit == 0)
	{
		signal(SIGQUIT, signal_quit);
		signal(SIGINT, signal_quit);
		ft_print_prompt();
		get_next_line(0, &line);
		ft_lstadd_front_hist(data, line);
		ft_exec_line(data);
	}
	return (0);
}

void		ft_print_prompt()
{
	write(1, "minishell$> ", 12);
}
