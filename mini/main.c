#include "minishell.h"

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
		ft_lstadd_front(data->historic, line);
		ft_parse_line(&data);
	}
	return (0);
}

void		ft_print_prompt()
{
	write(1, "--->", 4);
}

void		ft_parse_line(t_struct *data)
{
	char	**cmd;
	t_cmd	*lst_cmd;
	
	
	ft_init_lst(lst_cmd);
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i])
	{
		//fork?
		ft_treat(cmd[i], lst_cmd);
		i++;
	}
}

void		ft_treat(t_struct *data, char *line)
{
	char 	**cmd;

	cmd = ft_split_shell(line, '|');

}	
