#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

/* Data contains all the data of one input. This input is divided by prompts
(one prompt could be piped into another). Every Prompt is divided into tokens.
Every token has a tokentype */

typedef enum e_tokentype
{
	empty,
	word,
	option,
	value,
	redirection,
}	t_tokentype;


typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_tokentype	type;
}				t_token;

typedef struct s_data
{
	struct s_token	**tokens;
}	t_data;

int		main (void);
char	*prompt(void);
char 	**split_token(char *str);
int		load_tokens(char **split_tokens, t_data *data);

//Utils
int		is_char(char place, char c);
void	freestrings(char *s1, char *s2, char *s3, char **array);
char	*username(void);
void	switch_flag(int *flag);
void print_tokens (t_token **token);



#endif
