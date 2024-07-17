#include "macroshell.h"

void execute_command_in_bin(t_data *data)
{
	char *path;
    char *cmd;
    char **bins;
	pid_t	pid;
    int slash = 0;
    int i = 0;

    bins = data->bins;
	cmd = data->args[0];
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1); ///// ila kan prob d fork i exiquita progam kolo?
	}
    if (pid == 0)
	{
		while (cmd[i] != '\0')
    	{
    	    if (cmd[i] == '/')
    	    {
    	        slash = 1;
    	        break ;
    	    }
    	    i++;
    	}
    	if (slash == 1)
    	{
    	    execve(data->args[0], data->args, environ);
    	    perror("minishell");
    	    exit(1);
    	}
    	while (*bins)
    	{
    	    path = ft_strjoin(*bins, "/");
    	    cmd = ft_strjoin(path, data->args[0]);
    	    if (access(cmd, F_OK) == 0)
    	    {
				printf("[from bins]\n");
    	        execve(cmd, data->args, environ);
    	        perror("minishell");
    	        exit(1);
    	    }
    	    // free(path);
    	    // free(cmd);
    	    bins++;
    	}
    	ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(data->args[0], 2);
    	ft_putstr_fd(": command not found\n", 2);
	}
    if (pid > 0)
        waitpid(pid, NULL, 0); // an7tajha mn b3d 3la wed l parent (bach n catcher signals)
}

void execute_command(t_data *data)
{
	t_token *token = data->token;
 
	if (data->args[0] == NULL || data->args[0][0] == '\0')
		return;
	else if (ft_strcmp("exit", token->value) == 0)
		exit(0);
	else if (ft_strcmp(data->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->args[0], "cd") == 0)
	    ft_chdir(data);
	else if(ft_strcmp(data->args[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->args[0], "export") == 0)
		ft_export();
	else if (ft_strcmp(data->args[0], "env") == 0)
		ft_env();
	else
	 	execute_command_in_bin(data);
}

void execute_commands(t_data *data) 
{
	int pid;
    int pipefd[2];
	t_token *token = data->token;
	int fd_in = 0;
	int i = 0;

    //args = parse_commands(data);
	if (data->has_pipe == 0)
	{
		parse_args(data);
		execute_command(data);
	}

	if (data->has_pipe == 1)
	{
		//
	}
}
