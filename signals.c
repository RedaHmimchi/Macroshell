#include "macroshell.h"

void	sigint_handler(int sig) 
{
	if (sig == SIGINT) 
	{
		// rl_on_new_line();
   		// write(1, "\n", 1);
    	// rl_replace_line("", 0);
    	// rl_redisplay();
		printf("\n");
		rl_on_new_line();
    	rl_replace_line("", 0);
    	rl_redisplay();
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		return;
}

void	initialize_signals(t_data *data)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}