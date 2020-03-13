#include "../inc/minishell.h"

void		ft_init_data(t_data *data)
{
	data->historic = malloc(sizeof(t_hist));
	data->historic->next = NULL;
	data->lst_cmd = malloc(sizeof(t_cmd));
	data->lst_cmd->next = NULL;
	data->exit = 0;
}

void		ft_init_lst(t_cmd *lst_cmd)
{
}
