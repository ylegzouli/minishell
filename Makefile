.PHONY: all clean fclean re norme

CC = clang

FLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC_PATH = ./srcs
LIB_PATH = ./lib
INC_PATH = ./inc
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj

INC_NAME =	minishell.h
SRC_NAME =	main.c utils4.c utils3.c utils2.c pwd.c echo.c parsing_output.c parsing.c init.c exec_cmd.c env.c check_env.c \
			parsing_env.c env_cmd.c parsing_file.c export.c empty_pipe.c echo_suite.c  parsing_env_suite.c \
			free_env.c cd.c cd_dir.c exec_fork.c signal.c utils.c error.c export_no_arg.c free.c parsing_utils.c env_suite.c print_error.c ft_split_shell.c
LIB_NAME = isdigit.c ft_atoi.c ft_lst.c ft_lstclear.c  ft_strchr_shell.c ft_split_sh.c get_next_line.c ft_putchar_fd.c \
			get_next_line_utils.c ft_strdup.c ft_strcmp.c ft_split.c  ft_strnstr.c\
			ft_init_tab.c ft_bzero.c ft_strlcpy.c ft_strchr.c \
			ft_strncmp.c ft_strlen.c ft_lstadd_back.c ft_lstnew_malloc.c ft_putnbr_fd.c \
			ft_strtrim.c ft_lstsize.c ft_memcpy.c ft_isalpha.c

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	${CC} -Wall -Wextra -Werror -o ${NAME} ${OBJLIB} ${OBJ}

valgrind: $(OBJ) $(OBJLIB)
	${CC} -Wall -Wextra -Werror -g -o ${NAME} ${OBJLIB} ${OBJ} 
	valgrind --leak-check=full --show-leak-kinds=all ./minishell
	#valgrind --leak-check=full ./minishell

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	${CC} -o $@ -c $<

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(OBJLIB)

fclean: clean
	rm -rf ./obj $(NAME)

re: fclean all
