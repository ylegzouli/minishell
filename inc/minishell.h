#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/get_next_line.h"
# include "../lib/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define SUCCESS			0
# define ERROR_MALLOC		1

typedef struct	s_hist
{
	char			*line;
	struct s_hist	*next;
}				t_hist;

typedef struct	s_cmd
{
	int				cmd;
	char			*input;
	void			*result;	
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_data
{
	t_hist 			*historic;
	t_cmd			*lst_cmd;
	int				exit;
}				t_data;

//------------------------------ MINISHELL --------------------------------

int			ft_start(t_data *data);
void		ft_print_prompt();
void		ft_parse_line(t_data *data);
void		ft_treat(t_data *data, char *line);


//------------------------------- CMD ------------------------------------




//------------------------------- LIB ------------------------------------

void		ft_init_data(t_data *data);
void		ft_init_lst(t_cmd *lst_cmd);
int			ft_lstadd_front_hist(t_data *data, char *line);
void		ft_lstadd_front_cmd(t_data *data, t_cmd *new);
char		**ft_split_shell(char const *str, char charset);
//	ft_lstadd_back(lst_cmd, new);

//------------------------------------------------------------------------

#endif
