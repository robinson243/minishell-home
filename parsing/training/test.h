#ifndef TEST_H
# define TEST_H

# include "../../libft/libft.h"
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

typedef struct s_files
{
	int				fd;
	struct s_files	*next;
}					t_files;

typedef struct s_node
{
	int				type;
	char			*content;
	int				quoted;
	struct s_node	*next;
}					t_node;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_node			*tab_cmd;
}					t_cmd;

char				*extract_dollar(char *str, int *i);
char				*ft_strjoin_char(const char *s, char c);
char				*change_sentence(char *str);
char	*handle_quote_management(char *tmp, char *str, int *i);
char	*extract_word(char *str, int *i);
void	set_token_type(t_node *node);

#endif