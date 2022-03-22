NAME = minishell

FILES = 0_minishell.c 1_process_package.c 2_get_command.c 3_allocate_redirections.c 4_quote_rules.c 5_handle_quotes.c 6_exp.c 7_exec.c\
		special_pipe_split.c special_cmd_split.c print_stuff.c \
		./utils/sig_handls.c ./utils/builtins.c ./utils/ft_echo.c ./utils/ft_exe_cd.c \
		./utils/ft_env_func.c ./utils/ft_export_func.c ./utils/builtin_tools/handle_qouts.c ./utils/builtin_tools/handle_string.c 

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
