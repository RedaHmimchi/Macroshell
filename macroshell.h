
#ifndef MACROSHELL_H
# define MACROSHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

extern char **environ;

enum type
{
	WORD,
	PIPE,
	R_LEFT,
	R_RIGHT,
	R_D_RIGHT,
	R_D_LEFT
};

typedef struct s_token
{
    struct s_token    *next;
    char              *value;
    enum type    type;
}   t_token;


typedef struct s_data
{
	char    *cmd;
	char    *path;
	int     start_path;
	char	**bins;
	char	**args;
	t_token *token;
	int		has_pipe;
	int		num_pipes;
}	t_data;

//	libft
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t  ft_strlen(const char *str);
int     ft_strncmp(const char *str1, const char *str2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *str1, const char *str2);

//	parsing
void 	parse_command(char *input, t_data *data);
void	parse_args(t_data *data);
void	parse_bin(char *input, t_data *data);

// execution
void 	execute_commands(t_data *data);

// signals
void 	sigint_handler(int sig);
void 	sigquit_handler(int sig);
void 	initialize_signals();

// commands
void 	ft_chdir(t_data *data);
void 	ft_pwd();
void 	ft_echo(t_data *data);
void 	ft_export();

#endif