#include "../inc/minishell.h"

void		free_list_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(tmp->name);
		env = tmp->next;
		free(tmp);
		tmp = env;
	}
}

void		free_list_env(t_env *env)
{
	t_env	*tmp;

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

void		free_split(char **s)
{
	int		i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}
