# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 17:15:14 by lwoiton           #+#    #+#              #
#    Updated: 2023/08/16 12:43:33 by lwoiton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output files
NAME = pipex

# Directories
SRC_DIR = srcs
BONUS_DIR = bonus
OBJ_DIR = objs
BONUS_OBJ_DIR = $(OBJ_DIR)/$(BONUS_DIR)
INC_DIR = incl
LIB_DIR = libft

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INC_DIR) -I$(LIB_DIR)/incl
DBUG = -g

# Source files
SRC_FILES = 01_main.c


# Object files
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Header files
HEADER_FILES = $(wildcard $(INC_DIR)/*.h)

# Libraries
LIBFT = $(LIB_DIR)/libft.a

# Default targets
all: $(NAME)
bonus: $(BONUS_NAME)

# Rule to build the pipex executable
$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) -g -o $@ $^

# Rule to build object files and include header dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DBUG) -c -o $@ $<

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $@

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

# Clean generated files
clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)

# Clean and build everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re libft
