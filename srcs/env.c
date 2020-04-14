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
		ft_memcpy(ret + i, tmp->value, ft_strlen(tmp->value));
		i += ft_strlen(tmp->value);
		ret[i] = '\n';
		i++;
		tmp = tmp->next;
	}
	return (ret);
}

int				env(t_env *env, char **result)
{
	int		size;
	t_env	*tmp;
	char	*ret;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size += ft_strlen(tmp->name) + 1 + ft_strlen(tmp->value) + 1;
		tmp = tmp->next;
	}
	size++;
	if (!(ret = malloc(sizeof(char) * size)))
		return (1);
	ret[size] = '\0';	
	tmp = env;
	g_data->ret = 0;
	*result = env_copy(tmp, ret); // il faudrait free *result avant, non?
	return (0);	
}
