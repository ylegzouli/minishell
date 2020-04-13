#include "../inc/minishell.h"
extern char **environ;

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < (n - 1) && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - s2[i]);
}


int			check_variable_env(/*t_data *data, */ t_env *env, char *s)
{
	// il faut checker si la variable d'environnement existe
	t_env		*tmp;
	int			size;
	int			i;

	tmp = env;
	size = 0;
	i = 0;
	while (s[size] && s[size] != '=')
		size++;
	while (tmp)
	{
		if (ft_strncmp(s, tmp->name, size) != 0) // ce if peut etre dans le while peut etre
			tmp = tmp->next;
		else
		{
			free(tmp->value);
			size++;
			while (s[i + size])
				i++;
			if (!(tmp->value = malloc(sizeof(char) * (i + 1))))
				return (1); // m_error;
			tmp->value[i] = '\0';
			while (--i >= 0)
				tmp->value[i] = s[i + size];
			return (1);
		}
	}
	return (0);
}


int			new_variable_env(/*t_data *data,*/t_env *env, char *s)
	//										 s = "bonjour=5" par exemple
{
	t_env 	*tmp;
	int 	size;
	int		j;

	tmp = env;
	size = 0;
	if (check_variable_env(/*data, */env, s) == 1)
	{
		//data->ret = 0;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_env))))
		return (1); // m_error
	tmp = tmp->next; 
	while (s[size] && s[size] != '=')
		size++;
	if (!(tmp->name = malloc(sizeof(char) * (size + 1))))
		return (1); // return (m_error("Erreur: malloc name"));
	j = size + 1;
	tmp->name[size] = '\0';
	while (--size >= 0)
		tmp->name[size] = s[size];
	while (s[size + j])
		size++;
	if (!(tmp->value = malloc(sizeof(char) * (size + 1))))
		return (1); // return (m_error("Erreur : malloc env value));
	tmp->value[size] = '\0';
	while (--size >= 0)
		tmp->value[size] = s[j + size];
	tmp->next = 0;
	//data->ret = 0;
	return (0);
}

void			delete_var_env(/*t_data *data, */t_env *env, char *s)
{
	t_env 	*tmp;
	t_env	*tmp2;
	
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(s, tmp->name, ft_strlen(s)) != 0)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		else
		{
			free(tmp->value);
			free(tmp->name);
			tmp2->next = tmp2->next->next;
			free(tmp);
			break;
		}
	}
	//data->ret = 0;
}   // unset est toujours en return = 0 dans bash

int		size_var_env_not_found(char *line)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (line[i] && line[i] != '$')
		i++;
	i++;
	while (line[i + size] && line[i + size] != ' ')
		size++;
	return (size);
}

char	*var_env_not_found(t_env *env, char *line)
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
//	free(line); je l'ai mis en dur dans la stakc le premier pour l'instant
	return (ret);
}

char 	*var_env_found(t_env *env, char *line, t_env *tmp)
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
//	free(line); je l'ai mis en dur dans la stakc le premier pour l'instant
	return (ret);
}

// retourne un char * ? 
int			look_for_env_var(/*t_data *data, */t_env *env, char *line)
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

// création de l'historique
//int			start_env(t_data *data, t_env *env)
int main()
{
	int		i;
	int		size;
	int		j;
	char 	*s;
	t_env	*tmp;
	t_env	*begin;
	t_env	*env; // devrait etre une variable de la fonction

	i = 1;
	s = *environ;
	while (environ[i])
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
			begin = env; // oui je sais c'est moche ... une idée?
		tmp = env;
		env = env->next;
		i++;
	}
	tmp->next = 0;
	env = begin;
	  
	  ////// 
	new_variable_env(env, "mama=125"); 
	new_variable_env(env, "youpi=ameeeennn"); 
	new_variable_env(env, "var1=coucou1"); 
	new_variable_env(env, "var2=coucou2"); 
	new_variable_env(env, "var3=coucou3"); 
	new_variable_env(env, "mama=yolo"); 
	new_variable_env(env, "mama=ma nouvelle valeur"); 
	delete_var_env(env, "var1");
	delete_var_env(env, "je n'existe pas");
	  
		/*  TEST 1	   
	   while (env)
	   {
	   printf("%s=%s\n", env->name, env->value);
	   env = env->next;
	   }
		*/

	char str[38] = "echo $var2 $var1 $mama $nopnop $youpi";
	look_for_env_var(env, str);
	
}

