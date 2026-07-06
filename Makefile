NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

# ==== SOURCE ==== #

SRC_DIR = ./
SRC = \
	$(SRC_DIR)main.c

# ==== OBJ ==== #

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

# ==== Compilers ==== #

all: $(Name)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

obj/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==== Clean ==== #

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY all clean fclean re