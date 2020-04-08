#include "../inc/minishell.h"

int		main(int ac, char **av)
{
	t_data	data;

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

	i = 0;
	cmd = ft_split_shell(line, '|');
	ft_init_lst(new_cmd);
	while (cmd[i] && !(data->exit))
	{
		ft_init_lst(new_cmd);
		get_cmd(data, new_cmd, cmd[i]);
//		ft_lstadd_front_cmd(data, new_cmd);
		i++;
	}
	//ft_free_split(cmd);
}

//-------------------------------------------------------------

void		get_cmd(t_data *data, t_cmd *new_cmd, char *cmd)
{
	char **tmp;

	tmp = ft_split(cmd, ' ');
	if (ft_strcmp(tmp[0], "exit") == 0)
	{
		printf("exit\n");
		//il faut une fonction de nettoyage ici
		data->exit = 1;
	}
	else if (ft_strcmp(tmp[0], "echo") == 0)
	{
		printf("echo\n");
	//	get_opt();	
	//	get_input();
	//	new_cmd->ret = echo(new_cmd->input, new_cmd->result);
		char *str = 0;
		echo(cmd, str);
	}
	else if (ft_strcmp(tmp[0], "cd") == 0)
	{
		printf("cd\n");
	//	get_input();
	//	new_cmd->ret = cd(new_cmd->input, data->path);
	}
	else
		get_cmd2(data, new_cmd, tmp);
	//ft_free_split(tmp);
}

void		get_cmd2(t_data *data, t_cmd *new_cmd, char **tmp)
{
	if (ft_strcmp(tmp[0], "pwd") == 0)
	{	
		ft_pwd(data);
	}
	else if (ft_strcmp(tmp[0], "export") == 0)
	{
		printf("export\n");
	//	get_input();
	//	new_cmd->ret = export();
	}
	else if (ft_strcmp(tmp[0], "unset") == 0)
	{
		printf("unset\n");
	}
	else if (ft_strcmp(tmp[0], "env") == 0)
	{
		printf("env\n");
	//	new_cmd->ret = env();
	}
	else if (ft_strcmp(tmp[0], "$?") == 0)
	{
		check_return(data);
	//	new_cmd->ret = env();
	}
	else if (tmp[0])
		printf("command not found\n");
}

//-------------------------------------------------------------
