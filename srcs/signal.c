
#include "../inc/minishell.h"

void	signal_prevent(int sig)
{
	if (sig == SIGINT) // ctrl C ; checkez comportement sur les fork
	{
		g_data->ret = 130;
		write(1 , "\n", 1);
		ft_print_prompt();
	}
	if (sig == SIGQUIT)
	 {// ctrl + \    *  checker compt sur fork
		g_data->exit = 0;
	 }
}

void	signal_quit(int sig)
{

	if (sig == SIGQUIT)
	 {// ctrl + \    *  checker compt sur fork
		g_data->exit = 1;
		g_data->ret = 131;
	 	write(1, "Quit: core dumped\n", 18);
	 }
	if (sig == SIGINT) // ctrl C ; checkez comportement sur les fork
	{
		g_data->exit = 1;
		g_data->ret = 130;
		write(1 , "\n", 1);
	//	ft_print_prompt();
	}
}

