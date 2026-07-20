NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
              $(SRC_DIR)/init.c \
              $(SRC_DIR)/parsing.c \
              $(SRC_DIR)/utils.c \
              $(SRC_DIR)/coder.c \
              $(SRC_DIR)/monitor.c \
              $(SRC_DIR)/queue.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re