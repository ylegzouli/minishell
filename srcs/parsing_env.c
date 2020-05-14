#include "../inc/minishell.h"

char				*env_question_found(char *line)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = -1;
	j = 0;
	size = size_int(g_data->ret) + 1;
	if (!(ret = malloc(sizeof(char) * ft_strlen(line) + (size - 1) - 1)))
		return (0);
	ret[ft_strlen(line) + (size - 1) - 2] = '\0';
	while (line[++i] && line[i] != '$')
		ret[i] = line[i];
	while (--size > 0)
	{
		ret[i + j] = (g_data->ret / power_of_ten(size - 1)) + '0';
		g_data->ret = g_data->ret % power_of_ten(size - 1);
		j++;
	}
	i--;
	while (line[++i + 2]) 
		ret[i + j] = line[i + 2];
	return (ret);
}

static char			*var_env_not_found(t_env *env, char *line)
{
	int		i;
	int		len_var;
	int		size;
	char 	*ret;

	i = -1;
	if (check_var_env_return(line) == 1)
	{	
		ret = env_question_found(line);
		return (ret);
	}
	len_var = size_var_env_not_found(line);
	size = ft_strlen(line) - 1 - len_var + 1;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (0);
	ret[size] = '\0';
	while (line[++i] && line[i] != '$')
		ret[i] = line[i];
	i--;
	while (line[++i + len_var + 1])
		ret[i] = line[i + len_var + 1];
	return (ret);
}

static char 	*var_env_found(t_env *env, char *line, t_env *tmp)
{
	int		i;
	int		j;
	int		size;
	char 	*ret;

	i = -1;
	j = -1;
	size = ft_strlen(line) - 1 - ft_strlen(tmp->name)
			+ ft_strlen(tmp->value) + 1;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (0);
	ret[size] = '\0';
	while (line[++i] && line[i] != '$' && (ft_strncmp(line + i + 1,
				tmp->name, ft_strlen(tmp->name)) != 0))
		ret[i] = line[i];
	while (tmp->value[++j])
		ret[i + j] = tmp->value[j];
	while (line[i])
	{
		ret[i + j] = line[i + ft_strlen(tmp->name) + 1];
		i++;
	}
	return (ret);
}

char		*parse_env2(char *res, t_env *tmp, t_env *env, int i)
{
			if (res[i + 1] && tmp != 0 && (i + 1 + ft_strlen(tmp->name) >=
				ft_strlen(res) || res[i + 1 + ft_strlen(tmp->name)] == '$' ||
				res[i + 1 + ft_strlen(tmp->name)] == ' '))
				res = var_env_found(env, res, tmp);
			else
				res = var_env_not_found(env, res);

}

char		*parse_env(t_env *env, char *line)
{
	t_env 	*tmp;
	int		i;
	char	*res;

	i = -1;
	res = line;
	while (res[++i])
	{
		tmp = env;
		while (res[i] && res[i] != '$')
			i++;
		if (res[i])
		{
			while (res[i + 1] && tmp && (ft_strncmp(res + i + 1,
				tmp->name, ft_strlen(tmp->name)) != 0))
				tmp = tmp->next;
			res = parse_env2(res, tmp, env, i);
		}
	}
	free(line);
	return (res);
}
