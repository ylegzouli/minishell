#include "../inc/minishell.h"

int					check_cd_path(char *s)
{
	if (s)
	{
		if (s[0] == '.' && s[1] == '.')
			return (1);
		else if (s[0] == '.' && (s[1] == '\0' || s[1] == ' '))
			return (2);
		else if (s[0] != '\0')
			return (3);
		else
			return (4); // go home
	}
}
