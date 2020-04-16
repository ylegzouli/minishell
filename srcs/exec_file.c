#include "../inc/minishell.h"

int			exec_file(t_cmd *cmd)
{
	pid_t	pid;
	int		tube[2];
	char	*tmp;
	char	**arguments;
	char	**environnement;

	if (parsing_file(&environnement, &arguments, &tmp, cmd))
		return (1);
	if (pipe(tube) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(tube[0]);
		dup2(tube[1],1);
		if (execve(tmp, arguments, environnement) == -1)
			return (1);
		close(tube[1]);
		kill(pid, SIGKILL); // kill() ou exit() ? voir s'il y'a des leaks avec kill ?
	}
	else if (pid < 0)
		return (1);
	else
		cmd->result = get_result(tube, pid);
	free(tmp);
	//ft_free_split(arguments);
	//ft_free_split(environnement);
	return (0);
}

char		*get_result(int	tube[2], pid_t pid)
{
	char	buf;
	char	*result;

	close(tube[1]);
//	wait(&pid);
	result = malloc(sizeof(char));
	result[0] = 0;
	while (read(tube[0], &buf, 1) > 0)
	{	
		result = ft_add_char(result, buf);
		write(1, &buf, 1);
		// print_file();
	}
	wait(&pid);
	return (result);
}

void		print_file()
{
}
