# Minishell

This is a rebuild of *bash*.
This program can be separated into 3 Parts:

### 1.Lexer
Takes the input in form of a string and cuts it into words and signs.

### 2.Parser
Takes the strings from the Lexer and gives them a meaning. In other words creates tokens.
#### Token examples
| String  | Token |
|:----------:|----------|
| > | redirection |
| cat | command |
| -l | argument |
| \| | pipe |

A pipe signals the end of a command line and the beginning of a new one.
Every command line is being stored in an array.
Each command line consists of:
1. Command
2. Arguments
3. StdIn
4. StdOut

### 3.Executer
The executer will go through the array and executes each command one by one while also checking for possible redirections.
#### Redirection
Default for Input and Output is StdIn and StdOut. For each pipe-token, the StdOut gets geplaced by a file descriptor (fd). This fd[0] will be
connected to another fd[1]. This is a pipe. fd[1] is the input of the next command line.
\> and < tokens are redirections pointing to a custom file. A fd will be created for the file and Input or Output redirected to this fd.

Each execution of a command line runs in a different child process. This means everything is being executed at the same time.

Et voila!
Try it if you dare!

### Build
1. clone this repository
2. **`cd minishell`**
3. **`make`**
4. **`./minishell`**
