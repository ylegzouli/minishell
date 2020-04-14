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

//-- input/output --//
# define REDIRECT			1
# define PIPE				2
# define STDOUT				3
# define ARG				4

//-- commande --//
# define EXIT				1
# define ECHO				2
# define CD					3
# define PWD				4
# define EXPORT 			5
# define UNSET				6
# define ENV				7
# define NOTFOUND			8 // verifier si env=xx

//# define OPEN_MAX 256 // bug sur ordi arthur sinon

//------------------------------------------------------------------------

typedef struct		s_hist
{
	char			*line;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_cmd
{
	int				cmd;
	int				output;
	t_list			*fd_out;
	int				input;
	int				fd_in;
	char			*arg;
	char			*result;	
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*name;
	char			*value;
	char			**var_non_export_yet;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	t_hist 			*historic;
	t_cmd			*lst_cmd;
	t_env			*lst_env;

	int				exit;
	char			path[1000];
	char			*pipe;
	int				ret;
}					t_data;

extern	t_data		*g_data;
extern	char		**environ;

//------------------------------ MINISHELL --------------------------------

int					ft_start(t_data *data);
int					ft_init_data(t_data *data);
int					ft_init_env(t_env *env);
int					ft_init_lst(t_cmd **lst_cmd);
void				ft_print_prompt();
void				ft_exec_line(t_data *data);
void				executor(t_data *data, char *line);
void				ft_exec_cmd(t_cmd *cmd);

//------------------------------ PARSING ---------------------------------

int					ft_parse(t_cmd *new_cmd, char *cmd, int i, int size);
char				*parse_env(t_env *env, char *line);
int					get_output(t_cmd *new_cmd, char *cmd, int i, int size);
int					get_fd(t_cmd *new_cmd, char *cmd);
char				*get_path(char *str);
int					open_file(char *str, int opt);
void				clean_fdout(t_list **fd);
void				get_cmd(t_cmd *new_cmd, char *cmd);
int					get_input(t_cmd *new_cmd, char *cmd, int i, int size);
void				get_arg(char **arg, char *str);


//------------------------------- CMD ------------------------------------

void				pwd(t_data *data);
int					echo(char *input, char **result);
int         		export(t_env *env, char *s);
void				unset(t_env *env, char *s);
int					env(t_env *envi, char **res);

//------------------------------- LIB ------------------------------------

void				find_path(t_data *data);
void				ft_lstadd_back_cmd(t_cmd *new);
void				ft_lstadd_front_cmd(t_data *data, t_cmd *new);
int					ft_lstadd_front_hist(t_data *data, char *line);
char				**ft_split_shell(char const *str, char charset);
char				**ft_split_sh(char const *str, char charset);
char				*ft_strchr_shell(char const *s, int c);
void				ft_init_tab(int	*tab, int len);
char 				*ft_add_char(char *str, char c);
int					check_variable_env(t_env *env, char *s);

//void		check_return(t_data *data);
//void		print_lst(t_list *li);

//------------------------------------------------------------------------

#endif
