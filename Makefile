CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./parsing -I./exec -I./builtin -g3
LDFLAGS = -lreadline

NAME = minishell
SUPP_FILE = readline.supp

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c \
       builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c builtin/utils_builtin.c \
       exec/expand_star.c exec/exec2.c exec/exec.c exec/heredoc.c exec/init.c exec/redir.c exec/signal.c exec/utils.c \
       parsing/extract.c parsing/handle_expands.c parsing/handle_expands_utils.c parsing/lexer.c parsing/main.c parsing/utils_main.c parsing/mini_functions.c parsing/node.c parsing/parsing.c parsing/utility_parsing.c parsing/utils.c \
       exec/wait.c builtin/export_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(SUPP_FILE)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(SUPP_FILE):
	@echo "{\n   ignore_readline_leaks\n   Memcheck:Leak\n   ...\n   obj:*/libreadline.so.*\n}" > $(SUPP_FILE)
	@echo "{\n   ignore_all_system_libs\n   Memcheck:Leak\n   ...\n   obj:*/lib*/lib*.so*\n}" >> $(SUPP_FILE)
	@echo "{\n   ignore_bash_commands\n   Memcheck:Leak\n   ...\n   obj:/bin/*\n}" >> $(SUPP_FILE)
	@echo "{\n   ignore_usr_bin\n   Memcheck:Leak\n   ...\n   obj:/usr/bin/*\n}" >> $(SUPP_FILE)
	@echo "Suppression file created: $(SUPP_FILE)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 

fclean: clean
	rm -f $(NAME) $(SUPP_FILE)
	$(MAKE) -C $(LIBFT_DIR) fclean 

re: fclean all

supp: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=$(SUPP_FILE) -s ./$(NAME)

.PHONY: all clean fclean re supp
