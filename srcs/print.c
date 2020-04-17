#include "../inc/minishell.h"

void		ft_print_result(t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;
	
	if (!cmd->result)
		return ;
	if (cmd->output == PIPE)
	{
		if (g_data->pipe)
			free(g_data->pipe);
		g_data->pipe = ft_strdup(cmd->result);
	}
	if (cmd->fd_out->content)
	{
		tmp = cmd->fd_out;
		while (tmp)
		{
			fd = *(int *)tmp->content;
			write(fd, cmd->result, ft_strlen(cmd->result));
			tmp = tmp->next;
		}
	}
	if (cmd->output == STDOUT && cmd->cmd != EXEC)
		write(1, cmd->result, ft_strlen(cmd->result));
}
