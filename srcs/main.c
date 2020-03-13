#include "../inc/minishell.h"

int		main(int ac, char **av)
{
	t_struct	data;

	ft_init_data(&data);
	ft_start(&data);
	return (0);
}

int		ft_start(t_struct *data)
{
	char *line;

	while(data->exit == 0)
	{
		ft_print_prompt();
		//fork?
		get_next_line(0, &line);
		ft_lstadd_front_hist(&data, line);
		ft_parse_line(&data);
	}
	return (0);
}

void		ft_print_prompt()
{
	write(1, "--->", 4);
}

/*
**split cmd
*/

void		ft_parse_line(t_struct *data)
{
	char	**cmd;
	int		i;
	
	cmd = ft_split_shell(data->historic->line, ';');
	i = 0;
	while (cmd[i])
	{
		//fork?
		ft_treat(data, cmd[i]);
		i++;
	}
}

/*
**parse cmd
*/

void		ft_treat(t_struct *data, char *line)
{
	char 	**cmd;
	int		i;

	cmd = ft_split_shell(line, '|');
	i = 0;
	while (cmd[i])
	{
		//----->
		i++;
	}
}	
