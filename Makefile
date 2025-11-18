CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./parsing -I./exec -I./builtin -g3
LDFLAGS = -lreadline libft.a

NAME = minishell

SRCS = builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c \
       builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c builtin/utils_builtin.c \
       exec/exec2.c exec/exec.c exec/heredoc.c exec/init.c exec/redir.c exec/signal.c exec/utils.c \
       parsing/extract.c parsing/handle_expands.c parsing/lexer.c parsing/main.c parsing/mini_functions.c parsing/node.c parsing/parsing.c parsing/utility_parsing.c parsing/utils.c \
	   exec/wait.c builtin/export_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
