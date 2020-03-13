#include "../inc/minishell.h"

void		ft_init_data(t_data *data)
{
	data->historic->next = NULL;
	data->lst_cmd->next = NULL;
}

void		ft_init_lst(t_cmd *lst_cmd)
{
}
