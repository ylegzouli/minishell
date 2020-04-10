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
	}
	return (0);
}

void		ft_print_prompt()
{
	write(1, "minishell$> ", 12);
}

//-------------------------------------------------------------

void		ft_parse_line(t_data *data)
{
	char	**cmd;
	int		i;
	
	i = 0;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		ft_treat(data, cmd[i]);
		i++;
	}
	//ft_free_split(cmd);
}

void		ft_treat(t_data *data, char *line)
{
	char 	**cmd;
	t_cmd	*new_cmd;
	int		i;
	int		size;

	i = 0;
	size = 0;
	cmd = ft_split_shell(line, '|');
	while (cmd[size])
		size++;
	while (cmd[i] && !(data->exit))
	{
		ft_init_lst(&new_cmd);
		get_output(new_cmd, cmd[i], i, size);
		clean_fdout(&new_cmd->fd_out);
		get_cmd(new_cmd, cmd[i]);
		get_input(new_cmd, cmd[i], i, size);
		//ft_lstadd_back_cmd(new_cmd);
		i++;
		
		printf("cmd= %d\noutput= %d\ninput= %d\nfd_in= %d\nresult= %s\nret= %d\n-----\n", new_cmd->cmd, new_cmd->output, new_cmd->input, new_cmd->fd_in, new_cmd->result,  new_cmd->ret);		
	}
	//ft_free_split(cmd);
}

//-------------------------------------------------------------
