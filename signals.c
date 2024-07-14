#include "macroshell.h"
#include <sys/wait.h>
#include <unistd.h>

void	sigint_handler(int sig) 
{
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return;
	if (sig == SIGINT) 
	{
		write(1, "\n", 1);
    	rl_replace_line("", 0);
		rl_on_new_line();
    	rl_redisplay();
	}
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
		return;
}

void	initialize_signals()
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);

}