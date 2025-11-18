/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:25:49 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 17:02:02 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../exec/exec.h"
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

typedef struct s_node
{
	int				type;
	char			*content;
	int				quoted;
	struct s_node	*next;
}					t_node;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	int				pipe_out;
	int				quoted;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_files
{
	int				fd;
	struct s_files	*next;
}					t_files;

int					recognize_token(const char *s, int *i);
int					is_space(char c);
int					ft_strcmp(char *s1, char *s2);

t_node				*create_node(char *content, int quoted);
void				add_node(t_node **head, t_node *new);
void				clear_nodes(t_node **head);
void				print_list(t_node **head);

char				*ft_strjoin_free(char *s1, char *s2);
void				print_cmd_list(t_cmd *cmd);

char				*expand_dollar_basic(char *s, int *i, char **envp);
char				*expand_variables_basic(char *s, char **envp);

char				*extract_quoted(char *str, int *i);
char				*extract_single_quoted(char *str, int *i);
char				*extract_operator(char *str, int *i);
char				*extract_dollar(char *str, int *i, char **envp);
char				*extract_word(char *str, int *i, char **envp);
char				*handle_quote_management(char *tmp, char *str, int *i,
						char **envp);

char				*mini_double_quoted(char *input, int *i, int *quoted);
char				*mini_single_quoted(char *input, int *i, int *quoted);
void				gain_some_lines(t_cmd **cur_cmd, t_cmd **head_cmd);
void				handle_pipe(t_cmd **cur_cmd, t_node *tmp);

char				*build_word(char *input, int *i, int *quoted, char **envp);
t_node				*lexer(char *input, t_node **head, char **envp);
char				*find_path(char *str, char **envp);
t_node				*handle_expands(t_node **head, char **envp);
void				set_token_type(t_node *node);

void				process_word_node(t_cmd *cur_cmd, t_node *tmp,
						t_node **last_word_node);
void				process_pipe_node(t_cmd **cur_cmd, t_node *tmp,
						t_node **last_word_node);
/*Fonctions utilitaires pour le parsing final*/
void				add_arg(t_cmd *cmd, char *arg);
void				add_redir(t_cmd *cmd, t_redir *new);
t_cmd				*new_cmd(void);
t_redir				*new_redir(int type, char *file);
t_cmd				*parser(t_node **head);

void				free_cmd_list_no_files(t_cmd *head);

#endif