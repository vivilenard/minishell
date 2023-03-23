echo "pwd\n" | ./minishell 2>minishell_err >minishell_log
echo -n "enable -n .\npwd\n" | bash 2>bash_err >bash_log
echo "cd\n" | ./minishell 2>>minishell_err >>minishell_log
echo -n "enable -n .\ncd\n" | bash 2>>bash_err >>bash_log
echo "pwd\n" | ./minishell 2>minishell_err >minishell_log
echo -n "enable -n .\npwd\n" | bash 2>bash_err >bash_log