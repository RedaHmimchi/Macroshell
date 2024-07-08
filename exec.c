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
	if (ft_strcmp(data->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->args[0], "cd") == 0)
	    ft_chdir(data);
	else if(ft_strcmp(data->args[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->args[0], "export") == 0)
		ft_export();
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
	if (ft_strcmp("exit", token->value) == 0)
		exit(0);
	if (data->has_pipe == 0)
	{
		parse_args(data);
		execute_command(data);
	}
	if (data->has_pipe == 1)
	{
		parse_args(data);
		while (token != NULL)
		{
			if (token->type == WORD)
			{
				data->args[i++] = token->value;
				data->args[i] = NULL;
			}
			if (ft_strcmp(data->args[0], "exit") == 0)
				exit(0);
			if (token->type == PIPE)
			{
				if (token->type == PIPE)
				{
					pipe(pipefd);
					if ((pid = fork()) == -1)
					{
						perror("fork");
						exit(EXIT_FAILURE);
					}
					else if (pid == 0)
					{
						dup2(fd_in, 0); // change the input according to the old one 
						if (token->next != NULL)
							dup2(pipefd[1], 1);
						close(pipefd[0]);
						data->cmd = data->args[0];
						data->args = data->args;
						execute_command(data);
						exit(EXIT_FAILURE);
					}
					else
					{
						wait(NULL); // wait for process to finish
						fd_in = pipefd[0]; // save the input for the next command
					}
						
				}
				else
				{
					data->cmd = data->args[0];
					data->args = data->args;
					execute_command(data);
					break;
				}
				i = 0; // reset for next command
			}
			token = token->next;
		}
	}
	// while (token != NULL) 
	// {
	//     if (token->type == WORD) 
	//     {
	//         args[arg_index++] = token->value;
	//         args[arg_index] = NULL;
	//     }
	//     if (ft_strcmp(args[0], "exit") == 0)
	//         exit(0);
	//     if (token->type == PIPE) 
	//     {
	//         if (token->type == PIPE) 
	//         {
	//             pipe(pipefd);
	//             if ((pid = fork()) == -1) 
	//             {
	//                 perror("fork");
	//                 exit(EXIT_FAILURE);
	//             } 
	//             else if (pid == 0) 
	//             {
	//                 dup2(fd_in, 0); // change the input according to the old one 
	//                 if (token->next != NULL)
	//                     dup2(pipefd[1], 1);
	//                 close(pipefd[0]);
	//                 data->cmd = args[0];
	//                 data->args = args;
	//                 execute_command(data);
	//                 exit(EXIT_FAILURE);
	//             } 
	//             else
	//                 wait(NULL); // wait for process to finish
	//         }
	//         else
	//         {
	//             data->cmd = args[0];
	//             data->args = args;
	//             execute_command(data);
	//             break;
	//         }
	//         arg_index = 0; // reset for next command
	//     }
	//     token = token->next;
	// }
}

// void	execute_cmds(t_node **node, char **env, t_env **env_head, int *status)
// {
// 	t_var	var;
// 	t_node *curr;

// 	curr = *node;
// 	var.temp = -1;
// 	while (curr != NULL)
// 	{
// 		pipe(var.fd); // create a pipe for every command to be executed 
// 		if (check_if_builtins(curr) == 0) // if not a built-in command 
// 		{
// 			var.pid = fork(); // create a child process 
// 			if (var.pid == 0) // if child process 
// 			{
// 				if (curr->next == NULL) // if last command 
// 				{
// 					close(var.fd[1]); // close the write end of the pipe 
// 					dup2(var.temp, STDIN_FILENO); // change the input according to the old one
// 					close(var.fd[0]); // close the read end of the pipe
// 					close(var.temp); // close the temp file descriptor
// 					if (curr->fd_in != 0) // if input is not from stdin
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}
// 					if (execve(curr->path, curr->arg, env) == -1)
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 				}
// 				else if (var.temp == -1)
// 				{
// 					close(var.fd[0]);
// 					dup2(var.fd[1], STDOUT_FILENO);
// 					close(var.fd[1]);
// 					if (curr->fd_in != 0)
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}					
// 					if (execve(curr->path, curr->arg, env) == -1)
// 					{
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 					}
// 				}
// 				else
// 				{
// 					dup2(var.fd[1], STDOUT_FILENO);
// 					close(var.fd[1]);
// 					close(var.fd[0]);
// 					dup2(var.temp, STDIN_FILENO);
// 					close(var.temp);
// 					if (curr->fd_in != 0)
// 					{
// 						dup2(curr->fd_in, STDIN_FILENO);
// 						close(curr->fd_in);
// 					}
// 					if (curr->fd_out != 1)
// 					{
// 						dup2(curr->fd_out, STDOUT_FILENO);
// 						close(curr->fd_out);
// 					}
// 					if (execve(curr->path, curr->arg, env) == -1)
// 						put_error("command not found: ", curr->command);
// 						exit(127);
// 				}
// 			}
// 			else
// 			{
// 				close(var.fd[1]);
// 				if (var.temp != -1)
// 					close(var.temp);
// 				var.temp = var.fd[0];
// 				if (curr->next == NULL)
// 				{
// 					close(var.fd[0]);
// 					close(var.temp);
// 				}
// 			}
// 		}
// 		else if (check_if_builtins(curr) != 0 && curr->next == NULL)
// 		{
// 			close(var.fd[1]);
// 			close(var.fd[0]);
// 			close(var.temp);		
// 			*status = builtins(check_if_builtins(curr), curr, env_head, env);
// 		}
// 		else if (check_if_builtins(curr) != 0 && curr->next != NULL)
// 		{
// 			var.pid = fork();
// 			if (var.pid == 0)
// 			{
// 				close(var.fd[0]);
// 				dup2(var.fd[1], STDOUT_FILENO);
// 				close(var.fd[1]);
// 				*status = builtins(check_if_builtins(curr), 
//							curr, env_head, env);
// 				exit(0);
// 			}
// 			else
// 			{
// 				close(var.fd[1]);
// 				var.temp = var.fd[0];
// 			}
// 		}
// 		curr = curr->next;
// 	}
// 	while ((var.pid = wait(&var.waitstatus) != -1));
// 	if (var.waitstatus == -2)
// 		return ;
// 	makestatus(var.waitstatus, status);
// 	close(var.temp);
// }