NAME = macroshell
HEADER = macroshell.h
SRC = parsing.c main.c ./libft/tools.c ./libft/ft_split.c ./libft/ft_substr.c ./libft/ft_strjoin.c ./libft/ft_strdup.c exec.c signals.c cmds.c export.c
OBJ = $(SRC:.c=.o)
CFLAGS = -g

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

all: $(NAME)  

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -L$(READLINE_L) $^ -lreadline -o $@


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(READLINE_I) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all