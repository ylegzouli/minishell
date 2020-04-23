#include "../inc/minishell.h"

int			ft_init_data(t_data *data)
{
	int		i;

	i = -1;
	while (i++ < 1000)
		data->path[i] = '\0';
	find_path(data);
	if (!(data->historic = malloc(sizeof(t_hist))))
		return (ERROR_MALLOC);
	data->historic->next = NULL;
	if (!(data->lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
	if (!(data->lst_env = malloc(sizeof(t_env))))
		return (ERROR_MALLOC);
	if (!(data->lst_env_waiting = malloc(sizeof(t_env))))
		return (ERROR_MALLOC);
	data->lst_cmd->next = NULL;
	/////
	data->lst_env_waiting->name = malloc(1);
	data->lst_env_waiting->name[0] = '\0'; 
	data->lst_env_waiting->value = malloc(1);
	data->lst_env_waiting->value[0] = '\0'; 
	data->lst_env->next = NULL;
	data->lst_env_waiting->next = NULL;
	data->exit = 0;
	data->ret = 0;
	data->pipe = NULL;
	return (SUCCESS);
}

int			ft_init_env(t_env *env)
{
	int		i;
	int		size;
	int		j;
	char 	*s;
	t_env	*tmp;
	t_env	*begin;

	i = 1;
	s = *environ;
	while (environ[i - 1])
	{
		if (!(env = malloc(sizeof(t_env))))
			return (1); // return(m_error("Erreur: malloc t_env."));
		if (i > 1)
			tmp->next = env;
		size = 0;
		while (s[size] && s[size] != '=')
			size++;
		if (!(env->name = malloc(sizeof(char) * (size + 1))))
			return (1); // return (m_error("Erreur: malloc name"));
		j = size + 1;
		env->name[size] = '\0';
		while (--size >= 0)
			env->name[size] = s[size];
		while (s[size + j])
			size++;
		if (!(env->value = malloc(sizeof(char) * (size + 1))))
			return (1); // return (m_error("Erreur : malloc env value));
		env->value[size] = '\0';
		while (--size >= 0)
			env->value[size] = s[j + size];
		s = *(environ+i);
		env->next = 0;
		if (i == 1)
			begin = env;
		tmp = env;
		env = env->next;
		i++;
	}
	tmp->next = 0;
	g_data->lst_env = begin;
	return (0);
}

int			ft_init_lst(t_cmd **lst_cmd)
{
	if (!(*lst_cmd = malloc(sizeof(t_cmd))))
		return (ERROR_MALLOC);
	(*lst_cmd)->cmd = -1;
	(*lst_cmd)->input = -1;
	(*lst_cmd)->output = -1;
	(*lst_cmd)->fd_in = -1;
	if (!((*lst_cmd)->fd_out = malloc(sizeof(t_list))))
		return (ERROR_MALLOC);
	(*lst_cmd)->fd_out->content = 0;
	(*lst_cmd)->fd_out->next = NULL;
	(*lst_cmd)->result = NULL;
	(*lst_cmd)->next = NULL;
	return (SUCCESS);
}

