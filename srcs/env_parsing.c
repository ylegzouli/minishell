#include "../inc/minishell.h"

static char			*var_env_not_found(t_env *env, char *line)
{
	int		i;
	int		len_var;
	int		size;
	char 	*ret;

	i = 0;
	len_var = size_var_env_not_found(line);
	size = ft_strlen(line) - 1 - len_var + 1;
	if (!(ret = malloc(sizeof(char) * (size))))
		return (0);
	ret[size] = '\0';
	while (line[i] && line[i] != '$')
	{
		ret[i] = line[i];
		i++;
	}
	while (line[i])
	{
		ret[i] = line[i + len_var + 1];
		i++;
	}
	free(line);
	return (ret);
}

static char 	*var_env_found(t_env *env, char *line, t_env *tmp)
{
	int		i;
	int		j;
	int		size;
	char 	*ret;

	i = 0;
	j = 0;
	size = ft_strlen(line) - 1 - ft_strlen(tmp->name)
			+ ft_strlen(tmp->value) + 1;
	if (!(ret = malloc(sizeof(char) * (size))))
		return (0);
	ret[size] = '\0';
	while (line[i] && line[i] != '$' && (ft_strncmp(line + i + 1,
				tmp->name, ft_strlen(tmp->name)) != 0))
	{
		ret[i] = line[i];
		i++;
	}
	while (tmp->value[j])
	{
		ret[i + j] = tmp->value[j];
		j++;
	}
	while (line[i])
	{
		ret[i + j] = line[i + ft_strlen(tmp->name) + 1];
		i++;
	}
	free(line);
	return (ret);
}

int			look_for_env_var(t_env *env, char *line)
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
			if (tmp != 0 && (res[i + 1 + ft_strlen(tmp->name)] &&
		(res[i + 1 + ft_strlen(tmp->name)] == ' ') ||
		res[i + 1 + ft_strlen(tmp->name)] == '\0'))
			{
				res = var_env_found(env, res, tmp);
//				printf("Remplacement: \n%s\n", res);
			}
			else
			{
				res = var_env_not_found(env, res);
//				printf("Delete: \n%s\n", res);
			}
		}
		i++;
	}
}
