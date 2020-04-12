#include "../inc/minishell.h"

void		ft_exec_line(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		executor(data, cmd[i]);
		i++;
	}
	//ft_free_split(cmd);
}

void		executor(t_data *data, char *line)
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
		ft_parse(new_cmd, cmd[i], i, size);
		//ft_exec_cmd();
		//ft_lstadd_back_cmd(new_cmd);
		i++;

		printf("cmd= %d\noutput= %d\ninput= %d\nfd_in= %d\nresult= %s\nret= %d\n-----\n", new_cmd->cmd, new_cmd->output, new_cmd->input, new_cmd->fd_in, new_cmd->result,  new_cmd->ret);
	}
	//ft_free_split(cmd);
}
