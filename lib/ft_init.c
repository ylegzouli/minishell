#include "../inc/minishell.h"

int			ft_init_data(t_data *data)
{
	int		i;

	i = -1;
	while (i++ < 1000)
		data->path[i] = '\0';
	data->path[0] = '/';
	if (!(data->historic = malloc(sizeof(t_hist))))
		return (ERROR_MALLOC);
	data->historic->next = NULL;
	if (!(data->lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
	data->lst_cmd->next = NULL;
	data->exit = 0;
	return (SUCCESS);
}

int			ft_init_lst(t_cmd *lst_cmd)
{
	if (!(lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
//	lst_cmd->cmd = 0;
	lst_cmd->input = NULL;
	lst_cmd->result = NULL;
	lst_cmd->next = NULL;
	lst_cmd->ret = 0;
	return (SUCCESS);
}
