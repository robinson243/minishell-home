#ifndef TEST_H
# define TEST_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5
# define FILE 6


typedef struct s_node
{
	int				type;
	char			*content;
	int				quoted;
	struct s_node	*next;
}					t_node;

typedef struct s_files
{
	int				fd;
	struct s_files	*next;
}					t_files;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_node			*tab_cmd;
}					t_cmd;

int					recognize_token(const char *s, int *i);
int					is_space(char c);

t_node				*create_node(char *content, int quoted);
void				add_node(t_node **head, t_node *new);
void				clear_nodes(t_node **head);
void				print_list(t_node **head);

char				*ft_strjoin_free(char *s1, char *s2);

char				*expand_dollar_basic(char *s, int *i);
char				*expand_variables_basic(char *s);

char				*extract_quoted(char *str, int *i);
char				*extract_single_quoted(char *str, int *i);
char				*extract_operator(char *str, int *i);
char				*extract_word(char *str, int *i);
char				*extract_dollar(char *str, int *i);
char				*handle_quote_management(char *tmp, char *str, int *i);

char				*mini_double_quoted(char *input, int *i, int *quoted);
char				*mini_single_quoted(char *input, int *i, int *quoted);

char				*build_word(char *input, int *i, int *quoted);
t_node				*lexer(char *input, t_node **head);
t_node				*handle_expands(t_node **head);
void				set_token_type(t_node *node);

#endif