/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:00:18 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:33 by romukena         ###   ########.fr       */
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
	int				*infiles;
	int				inf;
	int				*outfiles;
	int				out;
	int				p_nb[2];
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_globale
{
	struct s_cmd	*cmd;
	struct s_node	*node;
}					t_globale;

int		ft_len(char *str);
char	*append_char(char *str, char c);
int		verif(int c, char *str);
int		ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *str, int types);
void	ft_lstclear(t_node **lst);
void	print_list(t_node *lst);
int		args_content(t_node **data, char *line);
int		all_parsing(t_globale **data, char *line);
t_cmd	*ft_lstnew_cmd(int nb_inf, int nb_out, int nb_cmd);

#endif