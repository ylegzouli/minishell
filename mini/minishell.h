#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_hist
{
	char			*line
	struct s_hist	*next;

}				t_cmd;

typedef struct	s_cmd
{
	char 			*line;
	char 			*ret;

}				t_cmd;

typedef struct	s_data
{
	t_hist 			*historic;

}				t_data;

//------------------------------ MINISHELL --------------------------------

int			ft_start(t_struct *data);
void		ft_print_prompt();
void		ft_parse_line(t_struct *data);
void		ft_treat(t_struct *data, char *line);

//------------------------------- LIB ------------------------------------

//	ft_init_data(&data);

//	ft_init_lst(new);
//	ft_lstadd_back(lst_cmd, new);
//	ft_lstadd_front(lst_cmd, new);

//	ft_split_shell(char *str, char sep);

//------------------------------------------------------------------------
#endif
