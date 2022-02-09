NAME = minishell

FILE = minishell.c \

CC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline

all: $(NAME)

$(NAME): $(FILE)
	$(CC) $(FLAGS) -o $(NAME) $(FILE)
	
#(FILE) as dependencya added, so changes in file are noticed and changed:)

fclean:
	rm -f $(NAME) 