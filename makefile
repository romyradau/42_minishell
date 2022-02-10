NAME = minishell

FILE = minishell.c parsing.c\

CC = gcc

FLAGS = -Wall -Wextra -Werror -lreadline

OBJ := $(FILES:.c=.o)

LINKED_OBJ = ./libft/*.o

all: linked_objects $(NAME)

$(NAME): $(FILE)
	$(CC) $(FLAGS) -o $(NAME) $(FILE) $(LINKED_OBJ)
	
linked_objects: 
	make -C ./libft
#(FILE) as dependencya added, so changes in file are noticed and changed:)

fclean:
	rm -f $(NAME) ./libft/*.o ./libft/*.a

make re: fclean all