# File name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude

# Directories
SRC_DIR = philo
OBJ_DIR = obj

# Source and object files
SRCS = $(wildcard *.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Text Colors
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

# targets
all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) 
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME) 
	@echo "fcleaned"

re: fclean all

.PHONY: all clean fclean re
