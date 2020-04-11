#include "../inc/minishell.h"

t_data          *g_data;

int		main(int ac, char **av)
{
	t_data	data;

	g_data = &data;
	ft_init_data(&data);
	ft_start(&data);
	//ft_free_data(&data);
	return (0);
}

int		ft_start(t_data *data)
{
	char *line;

	while(data->exit == 0)
	{
		ft_print_prompt();
		get_next_line(0, &line);
		ft_lstadd_front_hist(data, line);
		ft_parse_line(data);
		//ft_exec_cmd();
	}
	return (0);
}

void		ft_print_prompt()
{
	write(1, "minishell$> ", 12);
}
