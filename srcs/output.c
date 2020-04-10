#include "../inc/minishell.h"

int			get_output(t_cmd *new_cmd, char *cmd, int i, int size)
{
	get_fd(new_cmd, cmd);
	if (i < size - 1)
		new_cmd->output = PIPE;
	else if (i == size - 1 && ft_lstsize(new_cmd->fd_out) == 1)
		new_cmd->output = STDOUT;
	return (0);
}

int			get_fd(t_cmd *new_cmd, char *cmd)
{
	char		**tmp;
	int			i;
	int			fd;
	char		*path;

	tmp = ft_split_sh(cmd, '>');
	i = 1;
	while (tmp[i])
	{
		new_cmd->output = REDIRECT;
		path = get_path(ft_strtrim(tmp[i], " >"));
		if (tmp[i][0] == '>' && tmp[i][1] != '>')
			fd = open_file(path, 1);
		else
			fd = open_file(path, 2);
		ft_lstadd_back(&new_cmd->fd_out, ft_lstnew_malloc(&fd, sizeof(fd)));
		free(path);
		i++;
	}
	return (0);
}

int			open_file(char *str, int opt)
{
	int		fd;

	fd = -1;
	if (opt == 1)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0664);
	else if (opt == 2)
		fd = open(str, O_TRUNC | O_RDWR | O_CREAT, 0644);
	return (fd);
}

void		clean_fdout(t_list **fd)
{
	t_list	*tmp;

	if (ft_lstsize(*fd) > 1)
	{
		tmp = *fd;
		*fd = (*fd)->next;
		free(tmp);
	}
}

char		*get_path(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[0] == '/')
		return (str);
	else
	{
		while (g_data->path[i] != 0)
			i++;
		if (g_data->path[i - 1] != '/')
			g_data->path[i] = '/';
		tmp = ft_strjoin(g_data->path, str);
		g_data->path[i] = 0;
		return (tmp);
	}
}

//_____________________________________________________________________________

/*
void        print_lst(t_list *li)
{
    while (li != NULL)
    {
        printf("%d\n", (int)li->content);
        li = li->next;
    }
}
*/
