#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/get_next_line.h"
# include "../lib/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# define SUCCESS			0
# define ERROR_MALLOC		1

typedef struct	s_hist
{
	char			*line;
	struct s_hist	*next;
}				t_hist;

typedef struct	s_cmd
{
	char			*input;
	char			*result;	
	int				ret;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_data
{
	t_hist 			*historic;
	t_cmd			*lst_cmd;
	int				exit;
	char			path[1000];
}				t_data;

//------------------------------ MINISHELL --------------------------------

int			ft_start(t_data *data);
void		ft_print_prompt();
void		ft_parse_line(t_data *data);
void		ft_treat(t_data *data, char *line);

void		get_cmd(t_data *data, t_cmd *new_cmd, char *cmd);
void		get_cmd2(t_data *data, t_cmd *new_cmd, char **tmp);


//------------------------------- CMD ------------------------------------

void		pwd(char *path);
int			echo(char *input, char *result);


//------------------------------- LIB ------------------------------------

int			ft_init_data(t_data *data);
int			ft_init_lst(t_cmd *lst_cmd);
int			ft_lstadd_front_hist(t_data *data, char *line);
void		ft_lstadd_front_cmd(t_data *data, t_cmd *new);
char		**ft_split_shell(char const *str, char charset);
void		ft_init_tab(int	*tab, int len);
char 		*ft_add_char(char *str, char c);

//------------------------------------------------------------------------

#endif
