#include "../inc/minishell.h"

int			ft_parse(t_cmd *new_cmd, char *cmd, int i, int size)
{

	cmd = parse_env(g_data->lst_env, cmd);
	get_output(new_cmd, cmd, i, size);
	clean_fdout(&new_cmd->fd_out);
	get_cmd(new_cmd, cmd);
	get_input(new_cmd, cmd, i, size);
	return (0);
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
	{
		g_data->cmd_n_found = tmp[0];
		new_cmd->cmd = EXEC;
	}
	//ft_free_split(tmp);
}

int			get_input(t_cmd *new_cmd, char *cmd, int i, int size)
{
	char	**tmp;
	char	*tmp2;
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
	get_arg(&new_cmd->arg, tmp[0]);
	if (new_cmd->input == PIPE && new_cmd->cmd == EXEC)
	{
		//printf("%s\n", new_cmd->arg);
		new_cmd->arg = ft_add_char(new_cmd->arg, ' ');
//		new_cmd->arg = ft_add_char(new_cmd->arg, '"');
		tmp2 = ft_strjoin(new_cmd->arg, g_data->pipe);
		//printf("%s\n", tmp2);
		free(new_cmd->arg);
		new_cmd->arg = tmp2;
		new_cmd->arg = ft_add_char(new_cmd->arg, '"');
		//printf("[%s]\n", new_cmd->arg);
	}
//	else if (new_cmd->input == REDIRECT && new_cmd == EXEC)
//	{
//		
//	}
	//ft_free_split(tmp);
	// free tmp2
	return (0);
}

void		get_arg(char **arg, char *str)
{
	int		i;
	char 	**tmp;

	i = 0;
	tmp = ft_split_shell(str, '>');
	while (tmp[0][i] == ' ')
		i++;
	while (tmp[0][i] && tmp[0][i] != ' ')
		i++;
	while (tmp[0][i] == ' ')
		i++;
	*arg = ft_strdup(ft_strtrim(&tmp[0][i], " "));
	//ft_free_split(tmp);
}
