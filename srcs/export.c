#include "../inc/minishell.h"

int			check_arg_export(t_env *env, char *s, char **res, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (s[0] == '\0')
	{
		create_order_env(env, res, cmd);
		return (2);
	}
	while (s[i] && s[i] != '=')
	{
		if (ft_isalpha(s[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int			export2(t_env *tmp, char *s, int size)
{
	int j;

	j = 0;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_env))))
		return (1);
	tmp = tmp->next;
	while (s[size] && s[size] != '=')
		size++;
	if (!(tmp->name = malloc(sizeof(char) * (size + 1))))
		return (1);
	j = size + 1;
	tmp->name[size] = '\0';
	while (--size >= 0)
		tmp->name[size] = s[size];
	while (s[size + j])
		size++;
	if (!(tmp->value = malloc(sizeof(char) * (size + 1))))
		return (1);
	tmp->value[size] = '\0';
	while (--size >= 0)
		tmp->value[size] = s[j + size];
	tmp->next = 0;
	g_data->ret = 0;
}

int			export(t_env *env, char *s2, char **res, t_cmd *cmd)
{
	t_env	*tmp;
	int		i;
	char	**s1;

	if (s2[0] == '\0')
		return (create_order_env(env, res, cmd));
	s1 = ft_split(s2, ' ');
	i = -1;
	while (s1[++i])
	{
		tmp = env;
		if (check_arg_export(env, s1[i], res, cmd) == 1 &&
			(g_data->ret = 2) != 0)
			write(1, "export: bad variable name\n", 26);
		else if (check_variable_env(env, s1[i], check_char(s1[i], '=')) == 1)
			g_data->ret = 0;
		else if (check_variable_env(g_data->lst_env_waiting, s1[i],
					check_char(s1[i], '=')) == 1)
			switch_to_export(env, g_data->lst_env_waiting, s1[i]);
		else if (check_char(s1[i], '=') == 1)
			export2(tmp, s1[i], 0);
	}
	free_split(s1);
	return (0);
}
