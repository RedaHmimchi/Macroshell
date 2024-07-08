#include "macroshell.h"
#include <stdlib.h>

void	parse_bin(char *input, t_data *data)
{
	char	*path;
	char	*envp;
	
	envp = getenv("PATH");
	data->bins = ft_split(envp, ':');
	return;
}

void	count_pipes(char *input, t_data *data)
{
	int		count;
	int		i;
	
	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	if (count > 0)
		data->has_pipe = 1;
	data->num_pipes = count;
}

void parse_command(char *input, t_data *data)
{
	int i;
	char **tokens;
	t_token *token;
	t_token *last_token;

	i = 0;
	data->has_pipe = 0;
	count_pipes(input,data);
	tokens = ft_split(input, ' ');
	last_token = NULL;
	while (tokens[i] != NULL) {
		token = malloc(sizeof(t_token));
		token->value = ft_strdup(tokens[i]);
		token->next = NULL;

		if (ft_strcmp(tokens[i], "|") == 0)
			token->type = PIPE;
		else
			token->type = WORD;
		if (last_token == NULL)
			data->token = token;
		else
			last_token->next = token;
		last_token = token;
		i++;
	}

	// // Free
	// i = 0;
	// while (tokens[i] != NULL) 
	// {
	// 	free(tokens[i]);
	// 	i++;
	// }
	// free(tokens);
}

void parse_args(t_data *data) 
{
	int i = 0;
	t_token *token = data->token;
	int token_count = 0;

	// Count the number of tokens
	while (token != NULL) 
	{
		if (token->type == WORD) 
		{
			token_count++;
		}
		token = token->next;
	}

	// Allocate memory for data->args
	data->args = malloc((token_count + 1) * sizeof(char *));
	if (data->args == NULL) 
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// Reset token and i for the next loop
	token = data->token;
	i = 0;

	// Assign values to data->args
	while (token != NULL) 
	{
		if (token->type == WORD) 
		{
			data->args[i] = token->value;
			i++;
		}
		token = token->next;
	}
	data->args[i] = NULL;
}


