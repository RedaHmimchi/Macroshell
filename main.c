#include "macroshell.h"

int main()
{
	char *input;
	char prompt[256];
	t_data *data;
	char *line;

	data = malloc(sizeof(t_data));
	parse_bin(input, data);
	rl_catch_signals = 0;
    initialize_signals();
	while (69)
	{
		input = readline("macroshell$ ");
		if (input == NULL)
        {
			printf("bye bye\n");
            exit(0);
        }
		if (*input)
			add_history(input);
		parse_command(input, data);
        // EXECUTE THE COMMANDS
        execute_commands(data);
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