
#include "../inc/minishell.h"

void		free_list_env(t_env *env)
{
	t_env 	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->name);
		free(tmp->value);
		env = tmp->next;
		free(tmp);
		tmp = env;
	}
}
