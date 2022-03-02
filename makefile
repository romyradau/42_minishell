
NAME = minishell

FILES = 0_minishell.c 1_process_package.c 2_fill_package.c 3_package_calculator.c special_split.c print_stuff.c ./utils/sig_handls.c ./utils/builtins.c ./utils/ft_echo.c ./utils/ft_exe_cd.c \
		./utils/builtin_tools/handle_qouts.c ./utils/builtin_tools/handle_string.c 

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

CC = gcc 

CFLAGS = $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror -lreadline -g

OBJ := $(FILES:.c=.o)

LINKED_OBJ = ./libft/*.o

%.o: %.c
	@$(CC) -Wall -Wextra -Werror $(CPPFLAGS) $(INC) -o $@ -c $<
	@echo compiled $@

all: linked_objects $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LINKED_OBJ)
	
linked_objects: 
	make -C ./libft
#(FILE) as dependencya added, so changes in file are noticed and changed:)

fclean:
	rm -f $(NAME) ./libft/*.o ./libft/*.a $(OBJ)

make re: fclean all