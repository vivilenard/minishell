#include "../include/minishell.h"

// t_exec **init_exec0(t_exec **exec)
// {
// 	exec[0] = malloc (sizeof(t_exec));
// 	exec[0]->args = malloc(sizeof(char *));
// 	exec[0]->input = malloc(sizeof(char *)); 
// 	exec[0]->output = malloc(sizeof(char *)); 

// 	exec[0]->command = ft_strdup("/bin/cat");
// 	exec[0]->args[0] = ft_strdup("cat");
// 	exec[0]->args[1] = ft_strdup("head -5");
// 	exec[0]->input[0] = ft_strdup("<");
// 	exec[0]->input[1] = ft_strdup("in");
// 	exec[0]->output[0] = ft_strdup(">");
// 	exec[0]->output[1] = ft_strdup("out");

// 	printf("%s\n", exec[0]->command);
// 	printf("%s\n", exec[0]->args[0]);
// 	printf("%s\n", exec[0]->args[1]);
// 	printf("%s\n", exec[0]->input[0]);
// 	printf("%s\n", exec[0]->input[1]);
// 	printf("%s\n", exec[0]->output[0]);
// 	printf("%s\n", exec[0]->output[1]);
// 	return (exec);
// }
t_exec **init_exec0(t_exec **exec)
{
	exec[0] = malloc (sizeof(t_exec));
	exec[0]->args = malloc(sizeof(char *) * 3);
	exec[0]->input = malloc(sizeof(char *) * 3); 
	exec[0]->output = malloc(sizeof(char *) * 3); 

	//exec[0]->command = ft_strdup("/bin/echo");
	exec[0]->command = ft_strdup("/usr/bin/grep");
	exec[0]->args[0] = ft_strdup("grep");
	exec[0]->args[1] = ft_strdup("funny");
	exec[0]->args[2] = NULL;
	exec[0]->input[0] = ft_strdup("<");
	exec[0]->input[1] = ft_strdup("in.txt");
	exec[0]->input[2] = NULL;
	exec[0]->output[0] = ft_strdup("pipe");
	exec[0]->output[1] = ft_strdup("");
	exec[0]->output[2] = NULL;

	 //printf("%s\n", exec[0]->command);
	// printf("%s\n", exec[0]->args[0]);
	// printf("%s\n", exec[0]->args[1]);
	// printf("%s\n", exec[0]->input[0]);
	// printf("%s\n", exec[0]->input[1]);
	// printf("%s\n", exec[0]->output[0]);
	// printf("%s\n", exec[0]->output[1]);
	return (exec);
}
t_exec **init_exec1(t_exec **exec)
{
	exec[1] = malloc (sizeof(t_exec));
	exec[1]->args = malloc(sizeof(char *) * 3);
	exec[1]->input = malloc(sizeof(char *) * 3); 
	exec[1]->output = malloc(sizeof(char *) * 3); 

	//exec[1]->command = ft_strdup("/usr/bin/head");
	exec[1]->command = ft_strdup("/bin/cat");
	exec[1]->args[0] = ft_strdup("cat");
	exec[1]->args[1] = NULL;
	exec[0]->args[2] = NULL;
	exec[1]->input[0] = ft_strdup("pipe");
	exec[1]->input[1] = ft_strdup("");
	exec[0]->input[2] = NULL;
	exec[1]->output[0] = ft_strdup(">");
	exec[1]->output[1] = ft_strdup("out");
	exec[0]->output[2] = NULL;

	// printf("%s\n", exec[1]->command);
	// printf("%s\n", exec[1]->args[0]);
	// printf("%s\n", exec[1]->args[1]);
	// printf("%s\n", exec[1]->input[0]);
	// printf("%s\n", exec[1]->output[1]);
	return (exec);
}
// void init_exec1(t_exec *exec)
// {
// 	char *args[2] = {"head", "-5"};
// 	char *input[2] = {"<", "in"};
// 	char *output[2] = {">", "out"};

// 	exec[1].command = "/usr/bin/head";
// 	exec[1].args = args;
// 	exec[1].input = input;
// 	exec[1].output = output;

// 	printf("%s\n", exec[1].command);
// 	printf("%s\n", exec[1].args[0]);
// 	printf("%s\n", exec[1].args[1]);
// }
// void init_exec2(t_exec *exec)
// {
// 	char *args[2] = {"wc", NULL};
// 	char *input[2] = {"<", "in"};
// 	char *output[2] = {">", "out"};

// 	exec[2].command = "/usr/bin/wc";
// 	exec[2].args = args;
// 	exec[2].input = input;
// 	exec[2].output = output;
// }

int main ()
{
	t_exec **exec;

	exec = malloc (sizeof(t_exec *) * 3);
	exec = init_exec0(exec);
	printf("%s\n", exec[0]->command);
	exec = init_exec1(exec);
	exec[2] = NULL;
	executer(exec);

	return (0);
}

	// printf("%s\n", exec[0]->command);
	// printf("%s\n", exec[0]->args[0]);
	// printf("%s\n", exec[0]->args[1]);
	// printf("%s\n", exec[0]->input[0]);
	// printf("%s\n", exec[0]->output[1]);

	// printf("%s\n", exec[1]->command);
	// printf("%s\n", exec[1]->args[0]);
	// printf("%s\n", exec[1]->args[1]);
	// printf("%s\n", exec[1]->input[0]);
	// printf("%s\n", exec[1]->output[1]);