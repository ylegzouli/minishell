#include "../inc/minishell.h"

void		print_cmd_not_found(t_cmd *cmd)
{
	
	g_data->ret = 127;
	write(2, "minishell: ", 11);
	ft_putnbr_fd(cmd->nb_cmd, 2);
	write(2, ": ", 2);
	write(2, g_data->cmd_n_found, ft_strlen(g_data->cmd_n_found));
	if (cmd->arg[0] != 0)
	{
		write(2, " ", 1);
		write(2, cmd->arg, ft_strlen(cmd->arg));
	}
	write(2, ": not found\n", 12);
}


void		print_cd_error(char *s)
{

	write(2, "minishell: ", 11);
	ft_putnbr_fd(g_data->step_cmd, 2);
	write(2, ": cd: can't cd to ", 18);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}
