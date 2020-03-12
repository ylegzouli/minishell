#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>

# include "libft.h"

/*
# define ECHO = 1
# define CD = 2
# define PWD = 3
# define EXPORT = 4
# define UNSET = 5
# define ENV = 6
# define EXIT = 7
*/

typedef struct			s_list
{
	char				*content;
	int					index;
	struct s_list		list;
}						t_list;

typedef struct 			s_info
{
	int					past_return;
	t_list				list;
}						t_info;


#endif
