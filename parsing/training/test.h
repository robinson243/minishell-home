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

typedef struct s_files
{
	int	fd;
	struct s_files *next;
}	t_files;

typedef struct s_cmd
{
	char *word;
	bool mode_in_quote;
	char quote;
	struct s_cmd *next;
}	t_cmd;



#endif