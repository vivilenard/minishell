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
# include <signal.h>
# include <unistd.h>
# include <termios.h>

/* Data contains all the data of one input. This input is divided by prompts
(one prompt could be piped into another). Every Prompt is divided into tokens.
Every token has a tokentype */

typedef struct s_token 	t_token;

typedef enum e_tokentype
{
	word,
	option,
	variable,
	redirection,
	is_pipe,
}	t_tokentype;

typedef enum e_free_options
{
	everything,
	only_tokens,
}	t_free_options;


typedef struct s_token
{
	char		*content;
	t_token		*next;
	t_tokentype	type;
}				t_token;

typedef struct s_exec
{
	char			*command;
	char			**args;
	char			**input;											
	char			**output;
}				t_exec;

typedef struct s_data
{
	t_token			**tokens;
	int				token_count;
	t_exec			**execs;
	int				pipeflag;
}	t_data;

int			main (void);
char		*prompt(void);
char		**split_token(char *str);
int			load_tokens(char **split_tokens, t_data *data);
t_tokentype	content_analyse(t_token *token);
int 		parse_tokens(t_data *data);


//Utils
int		is_char(char place, char c);
void	freestrings(char *s1, char *s2, char *s3, char **array);
char	*username(void);
void	switch_flag(int *flag);
void	print_tokens (t_token **token);
void 	free_tokens(t_token **token, t_free_options type);
void	free_data(t_data *data);
void	init_data(t_data *data);

//Utils Parser
void	print_execs(t_data *data);
int		get_exec_count(t_token	*current);
int		get_arg_num(t_token *current);


//Split
int	is_delimiter(char c);
char **makestring(char **split, char *str, int start, int i);
int jump_delimiters(char *str, int *i);
int	jump_redir(char *str, int *i);


#endif
