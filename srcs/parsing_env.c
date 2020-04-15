#include "../inc/minishell.h"

static int			size_var_env_not_found(char *line)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (line[i] && line[i] != '$')
		i++;
	i++;
	while (line[i + size] &&
		(line[i + size] != ' ' || line[i + size] != '$'))
		size++;
	return (size);
}

int					check_var_env_return(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?')
				return (1);
		}
		i++;
	}
	return (0);
}

char				*env_question_found(char *line)
{
	int		i;
	char	*ret;

	i = 0;
	if (!(ret = malloc(sizeof(char) * ft_strlen(line))))
		return (0); ////
	ret[ft_strlen(line) - 1] = '\0';
	while (line[i] && line[i] != '$')
	{
		ret[i] = line[i];
		i++;
	}
	ret[i] = g_data->ret + '0';
	i++;
	while (line[i + 1])
	{
		ret[i] = line[i + 1];
		i++;
	}
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
		free(line);
		return (ret);
	}
	len_var = size_var_env_not_found(line);
	size = ft_strlen(line) - 1 - len_var + 1;
	if (!(ret = malloc(sizeof(char) * (size))))
		return (0);
	ret[size] = '\0';
	while (line[++i] && line[i] != '$')
		ret[i] = line[i];
	i--;
	while (line[++i])
		ret[i] = line[i + len_var + 1];
	free(line);
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
	if (!(ret = malloc(sizeof(char) * (size))))
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
	free(line);
	return (ret);
}

char		*parse_env(t_env *env, char *line)
{
	t_env 	*tmp;
	int		i;
	char	*res;

	i = 0;
	res = line;
	while (res[i])
	{
		tmp = env;
		while (res[i] && res[i] != '$')
			i++;
		if (res[i])
		{
			while (tmp && (ft_strncmp(res + i + 1,
				tmp->name, ft_strlen(tmp->name)) != 0))
				tmp = tmp->next;
			if (tmp != 0 && ((res[i + 1 + ft_strlen(tmp->name)] &&
		(res[i + 1 + ft_strlen(tmp->name)] == ' ' ||
		res[i + 1 + ft_strlen(tmp->name)] == '$')) ||
		res[i + 1 + ft_strlen(tmp->name)] == '\0'))
				res = var_env_found(env, res, tmp);
			else
				res = var_env_not_found(env, res);
		}
		i++;
	}
	return (res);
}
