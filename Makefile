NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

# ==== SOURCE ==== #
SRC_DIR = src/
SRC_FILES = main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

# ==== HEADER ==== #
HEADER = $(SRC_DIR)codexion.h

# ==== OBJ ==== #
OBJ_DIR = obj/
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# ==== RULES ==== #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ==== Clean ==== #
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re