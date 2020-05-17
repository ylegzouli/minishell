#include "../inc/minishell.h"

void		get_empty_pipe(char **cmd)
{
	char	*tmp;
	char	*line;

	g_data->empty_pipe = 0;
	tmp = ft_strtrim(*cmd, " ");
	if (tmp[ft_strlen(tmp) - 1] == '|')
	{
		g_data->empty_pipe = 1;
		free(*cmd);
		write(1, "> ", 2);
		get_next_line(0, &line);
		*cmd = ft_strjoin(tmp, line);
		free(line);
		get_empty_pipe(cmd);
	}
	free(tmp);
}


