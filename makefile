NAME = minishell

FILE = minishell.c \

CC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -o $(NAME) $(FILE)

fclean:
	rm -f $(NAME) 