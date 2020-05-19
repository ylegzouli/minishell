#include "../inc/minishell.h"

void		free_cmd(t_cmd *lst_cmd)
{
	t_cmd *tmp;
	t_cmd *tmp2;

	tmp = lst_cmd;
	while (tmp)
	{
		ft_lstclear(&tmp->fd_out, &free);
		free(tmp->arg);
		free(tmp->result);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void		free_hist(t_hist *h)
{
	t_hist *tmp;
	t_hist *tmp2;

	tmp = h;
	while (tmp)
	{
		free(tmp->line);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

void		free_data()
{
	free_list_env(g_data->lst_env);
	free_list_env(g_data->lst_env_waiting);
	free_cmd(g_data->lst_cmd);
	free_hist(g_data->historic);
	free(g_data->pipe);
	//free(g_data->cmd_n_found);
	free_split(g_data->cmd);
}
