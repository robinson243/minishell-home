/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:00:18 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/26 16:36:46 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "limits.h"
# include "stdbool.h"
# include <sys/stat.h>
# include "wait.h"
# include "signal.h"

# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5

# define LIM 6
# define INFILE 7
# define OUTFILE 8
# define OUT_APPEND 9

# define ERROR_SYNTAX "minishell: syntaxe error near unexpected token:"

extern int	g_signal;

typedef struct s_node
{
	int				type;
	char			*content;
	int				id;
	struct s_node	*next;
}					t_node;

typedef struct s_file
{
	char			*path;
	int				fd;
	int				type;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	char			**command;
	int				p_nb[2];
	int				prev_nb;
	int				infile;
	int				outfile;
	bool			skip_cmd;
	int				exit_code;
	bool			first;
	t_file			*list;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_globale
{
	char			**env;
	struct s_cmd	*cmd;
	struct s_node	*node;
	pid_t			signal;
	int				exit_code;
}					t_globale;

char	*append_char(char *str, char c);
int		verif(int c, char *str);
int		ft_lstaddback(t_node **lst, t_node *new);
t_node	*ftlstnew(char *str, int types);
void	ftlstclear(t_node **lst);
void	print_list(t_node *lst);
int		args_content(t_node **data, char *line);
int		all_parsing(t_globale **data, char *line);
t_cmd	*ft_lstnew_cmd(int nb_inf, int nb_out, int nb_cmd);
int		ft_pwd(void);
void	my_close(int fd1, int fd2, int fd3, int fd4);
char	*ft_strslashjoin(char const *s1, char const *s2);
void	free_all(char **str);
int		my_open(t_file *list, t_cmd *cmd);
int		is_builtin(char	*command);
char	**ft_unset(char **cmd, char	**env);
void	ft_exit(t_globale *data, t_cmd *cmd);
int		ft_pwd(void);
int		env(char **env);
int		ft_cd(char	**cmd, char **env);
void	redir_in_out(t_cmd *cmd);
int		do_builtin(t_globale *data, t_cmd *cmd);
int		here_doc(t_file *file);
void	redir_out(t_cmd *cmd);
void	free_exit(t_globale *data, char *str, int code);
int		ft_echo(char **args);
int		exist(char *cmd, char **path, t_globale *data);
char	*get_path(char **env, char *cmd, t_globale *data);
int		open_file(t_cmd *cmd);
int		check_dir(char **path, char *cmd, t_globale *data);

#endif