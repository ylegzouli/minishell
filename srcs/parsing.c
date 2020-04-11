#include "../inc/minishell.h"

void		ft_parse_line(t_data *data)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split_shell(data->historic->line, ';');
	while (cmd[i] && !(data->exit))
	{
		ft_parse_cmd(data, cmd[i]);
		i++;
	}
	//ft_free_split(cmd);
}

void		ft_parse_cmd(t_data *data, char *line)
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

void        get_cmd(t_cmd *new_cmd, char *cmd)
{
    char **tmp;

    tmp = ft_split(cmd, ' ');
    if (ft_strcmp(tmp[0], "exit") == 0)
		new_cmd->cmd = EXIT;
	else if (ft_strcmp(tmp[0], "echo") == 0)
		new_cmd->cmd = ECHO;
	else if (ft_strcmp(tmp[0], "cd") == 0)
		new_cmd->cmd = CD;
	else if (ft_strcmp(tmp[0], "pwd") == 0)
		new_cmd->cmd = PWD;
	else if (ft_strcmp(tmp[0], "export") == 0)
		new_cmd->cmd = EXPORT;
	else if (ft_strcmp(tmp[0], "unset") == 0)
		new_cmd->cmd = UNSET;
	else if (ft_strcmp(tmp[0], "env") == 0)
		new_cmd->cmd = ENV;
	else if (tmp[0])
		new_cmd->cmd = NOTFOUND;
	//ft_free_split(tmp);
}

int			get_input(t_cmd *new_cmd, char *cmd, int i, int size)
{
	char	**tmp;
	int		j;
	char	*path;

	tmp = ft_split_shell(cmd, '<');
	if (tmp[1] && new_cmd->fd_in == -1)
	{
		new_cmd->input = REDIRECT;
		path = get_path(ft_strtrim(tmp[1], " "));
		new_cmd->fd_in = open(path, O_RDONLY);
		free(path);
	}
	if (i > 0)
		new_cmd->input = PIPE;
	else if (!tmp[1])
		new_cmd->input = ARG;
	//ft_free_split(tmp);
	return (0);
}
