/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dems <dems@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:06:22 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/19 12:35:19 by dems             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "../parsing/test.h"
# include "limits.h"
# include "signal.h"
# include "stdbool.h"
# include "wait.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>

# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5

# define LIM 6

# define ERROR_SYNTAX "minishell: syntaxe error near unexpected token:"

extern pid_t			g_signal;

typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_node	t_node;

typedef struct s_exec
{
	t_cmd				*cmd;
	int					p_nb[2];
	bool				skip_cmd;
	int					exit_code;
	bool				first;
	int					prev_nb;
	int					infile;
	int					outfile;
	struct s_exec		*next;
}						t_exec;

typedef struct s_globale
{
	char				**env;
	t_exec				*exec;
	int					exit_code;
	t_node				*node;
	char				*line;
	int					preview_code;
}						t_globale;

int						ft_pwd(void);
void					my_close(int fd1, int fd2, int fd3, int fd4);
char					*ft_strslashjoin(char const *s1, char const *s2);
void					free_all(char **str);
int						my_open(t_redir *list, t_exec *exec);
int						is_builtin(char *command);
char					**ft_unset(char **cmd, char **env, t_exec *exec);
void					ft_exit(t_globale *data, t_cmd *cmd, t_exec *exec, int std);
int						ft_pwd(void);
int						env(char **env);
int						ft_cd(char **cmd, char **env);
void					redir_in_out(t_exec *exec);
void					do_builtin(t_globale *data, t_exec *exec);
void					redir_out(t_exec *exec);
void					free_exit(t_globale *data, char *str, int code);
int						ft_echo(char **args);
int						exist(char **path, t_cmd *command, t_globale *data,
							t_exec *exec);
char					*get_path(char **env, char *cmd,
							t_exec *exec);
void					open_file(t_exec *exec);
int						check_dir(char **path, char *cmd, t_cmd *command,
							t_exec *exec);
int						my_here_doc(char *limiter);
int						existe(char *str, char **env);
void					ft_swap(int i, int j, char **tab);
char					**ft_strdupdup(char **str);
int						len_list(char **env);
int						exec(t_cmd *command, char ***env, t_node *node,
							int prv_code);
char					**ft_export(char **cmd, char **env,
							t_exec *exec);
void					handle_sigint(int code);
void					free_exec(t_globale *data);
void					init_data(t_globale *data, t_node *node,
							int prv_code);
void					handle_sigint_child(int sig);
t_exec					*init_exec(t_cmd *cmd);
void					setup_signals_parent(void);
int						is_num(char *str);
void					wait_all(int *exit_code);
void					lst_clear(t_redir **lst);
int						export_noargs(char **env);
int						invalide_arg(char *str);
char					*normalize_export_arg(char *arg);
void					next(t_exec *exec);

#endif
