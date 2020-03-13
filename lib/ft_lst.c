#include "../inc/minishell.h"

int			ft_lstadd_front_hist(t_data *data, char *line)
{
	t_hist	*new;

	if (!(new = malloc(sizeof(t_hist))))
		return (ERROR_MALLOC);
	new->line = ft_strdup(line);
	new->next = data->historic->next;
	data->historic = new;
	return (SUCCESS);
}

void			ft_lstadd_front_cmd(t_data *data, t_cmd *new)
{
	new->next = data->lst_cmd->next;
	data->lst_cmd = new;
}
