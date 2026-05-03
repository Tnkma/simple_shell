CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g

SRC = main.c cus_fuc.c get_line.c fork_cmd.c builtin_cmd.c command_path.c logical_op.c read_input.c to_print.c help_me.c func_prot.c

OBJ = $(SRC:.c=.o)

NAME = hsh

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all