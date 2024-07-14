#include "macroshell.h"

int main()
{
	char *input;
	char prompt[256];
	t_data *data;
	char *line;

	data = malloc(sizeof(t_data));
	parse_bin(input, data);
	while (69)
	{
    	initialize_signals();
		input = NULL;
		input = readline("macroshell$ ");
		if (input == NULL)
        {
			printf("exit\n");
            exit(0);
        }
		
		if (input)
		{
			if (*input == '\0') // Check if input is an empty string
    		{
    	   		free(input); // Free the allocated memory to avoid memory leaks
    	    	continue; // Skip the rest of the loop and start over
    		}
			add_history(input);
			parse_command(input, data);
        	execute_commands(data);
		}
        // EXECUTE THE COMMANDS
		// // PRINT THE TOKENS
		// t_token *token = data->token;
		// while (token != NULL)
		// {
		// 	printf("Token: %s", token->value);
		// 	printf("	Type: %d\n", token->type);
		// 	token = token->next;
		// }
		free(input);
	}
}