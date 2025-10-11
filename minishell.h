/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:00:18 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/11 20:50:42 by ydembele         ###   ########.fr       */
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


# define WORD 0
# define PIPE 1
# define REDIR_IN 2
# define REDIR_OUT 3
# define REDIR_APPEND 4
# define HEREDOC 5

# define LIM 6
# define INFILE 7
# define OUTFILE 8

# define ERROR_SYNTAX "minishell: syntaxe error near unexpected token:"

// enum e_token
// {
// 	WORD,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	HEREDOC,
// 	LIM,
// 	INFILE,
// 	OUTFILE,
// };


typedef struct s_file
{
	char			*path;
	int				fd;
	int				way_open;
	struct s_file	*next;
}					t_file;

typedef struct s_node
{
	int				type;
	char			*content;
	int				id;
	struct s_node	*next;
}					t_node;

typedef struct s_cmd
{
	char			**command;
	char			*path;
	char			**skipfile;
	int				nb_infile;
	int				nb_outfile;
	char			*lim;
	bool			here_doc;
	char			*inf;
	char			*out;
	int				prev_nb;
	int				p_nb[2];
	bool			first;
	char			**env;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_globale
{
	char			**env;
	struct s_cmd	*cmd;
	struct s_node	*node;
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

#endif