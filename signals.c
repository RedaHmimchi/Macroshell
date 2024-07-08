#include "macroshell.h"

void sigint_handler(int sig) 
{
    if (sig == SIGINT) 
    {
        // printf("\n");
        write(1, "\nmacroshell$ ", 13);
	    // rl_replace_line("", 1);
        // rl_on_new_line();
	    rl_redisplay();
    }
}

void    sigquit_handler(int sig)
{
    if (sig == SIGQUIT)
        return;
}

void   initialize_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}