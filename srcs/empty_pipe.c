#include "../inc/minishell.h"

void		get_empty_pipe(char *cmd)
{
	char	*tmp;

	g_data->empty_pipe = 0;
	tmp = ft_strtrim(cmd, " ");
	if (tmp[ft_strlen(tmp) - 1] == '|')
		g_data->empty_pipe = 1;
	free(tmp);
}


