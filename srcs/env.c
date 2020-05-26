#include "../inc/minishell.h"

static char		*env_copy(t_env *tmp, char *ret)
{
	int		i;

	i = 0;
	while (tmp)
	{
		ft_memcpy(ret + i, tmp->name, ft_strlen(tmp->name));
		i += ft_strlen(tmp->name);
		ret[i] = '=';
		i++;
		ft_memcpy(ret + i, get_env_value(g_data->lst_env, tmp->name),
		ft_strlen(get_env_value(g_data->lst_env, tmp->name)));
		i += ft_strlen(get_env_value(g_data->lst_env, tmp->name));
		ret[i] = '\n';
		i++;
		tmp = tmp->next;
	}
	ret[i] = '\0';
	return (ret);
}

int				env(t_env *env, char **result,
			t_cmd *cmd, int print)
{
	int		size;
	t_env	*tmp;
	char	*ret;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size += ft_strlen(tmp->name) + 1 +
		ft_strlen(get_env_value(g_data->lst_env, tmp->name)) + 1;
		tmp = tmp->next;
	}
	size++;
	if (!(ret = malloc(sizeof(char) * size)))
		return (1);
	ret[size] = '\0';
	tmp = env;
	g_data->ret = 0;
	*result = env_copy(tmp, ret);
	if (print == 1)
		ft_print(*result, ft_strlen(*result), cmd, 0);
	return (0);
}

static int		export_env_w(t_env *tmp, char *s)
{
	int		j;
	int		size;

	size = 0;
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
	if (s[size + j - 1] == '"' || s[size + j - 1] == 39)
		return (export_quoted(tmp, s, size, j));
	else
		return (export_no_quote(tmp, s, size, j));
	return (0);
}

char		*get_cmd_n_found(t_cmd *cmd)
{
	char 	**tmp;
	char	*nl;

	tmp = ft_split_shell(cmd->cmd_temp, ' ');
	nl = ft_strdup(tmp[0]);
	free_split(tmp);
	return (nl);
}

int				command_var_env(t_env *env,
		t_env *env_w, char *line, t_cmd *cmd)
{
	int		i;
	t_env	*tmp;
	char	*nl;

	tmp = env_w;
	i = 0;
	nl = get_cmd_n_found(cmd);
	if (check_char(line, '=') == 0)
		return (-1);
	if (check_variable_env(env, line, check_char(nl, '=')) == 1 ||
		check_variable_env(env_w, line, check_char(nl, '=')) == 1)
	{
		g_data->ret = 0;
		free(nl);
		return (0);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	if (export_env_w(tmp, nl) == 1)
	{
		free(nl);
		return (1);
	}
	return (0);
}

char			*get_env_value(t_env *env, char *name)
{
	t_env		*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) != 0)
			tmp = tmp->next;
		else
			return (tmp->value);
	}
	return (0);
}
