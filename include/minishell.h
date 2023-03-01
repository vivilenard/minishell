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

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_tokentype		type;
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
}	t_data;

char		*prompt(void);
char		**split_token(char *str);
int			load_tokens(char **split_tokens, t_data *data);
t_tokentype	content_analyse(t_token *token);

//Utils
int			is_char(char place, char c);
void		freestrings(char *s1, char *s2, char *s3, char **array);
char		*username(void);
void		print_tokens(t_token **token);
void		free_data(t_data *data);
void	init_data(t_data *data);

//Lexer
char		**allocate(char **split, int strnumber);
char		**makestring(char **split, char *str, int start, int i);
int			is_delimiter(char c);
int			jump_delimiters(char *str, int *i);
int			jump_redir(char *str, int *i);
int			jump_delimiter_split(char **split, char *str, int *start, int *i);
void		switch_flags(int *flag, int quote, int *keep_quote);
int			handle_quote(char *str, int *i, int *flag, int *keep_quote);

//executer
int			executer(t_exec **exec, char **env);
int			in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe);
int			file_as_stdin(t_exec *exec);
int			file_as_stdout(t_exec *exec);
int			pipe_as_stdin(int fd_keep_pipe);
int			pipe_as_stdout(int *fd_pipe);
void		close_pipe(int *fd_pipe);
int			built_in(t_exec *exec, char **env);

#endif
