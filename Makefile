# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwoiton <lwoiton@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 17:15:14 by lwoiton           #+#    #+#              #
#    Updated: 2023/09/11 19:11:22 by lwoiton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output files
NAME = pipex
BNS_NAME = pipex

# Directories
SRC_DIR = srcs
INC_DIR = incl

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -Iincl -Ilibft/incl
DBUG = -g

# Library
LIBFT = libft/libft.a

# Source files
SRC_FILES = srcs/01_main.c srcs/02_utils.c

# Source files for bonus
BNS_FILES = srcs/01_main_bonus.c srcs/02_utils.c

# Header files
HEADER_FILES = pipex.h

BNS_HEADER_FILES = pipex_bonus.h

# Default rule to build the pipex executable
all: $(SRC_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $(LIBFT) $(SRC_FILES) -Llibft -lft -o pipex

# Bonus rule to build the pipex executable
bonus: $(BNS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $(LIBFT) $(BNS_FILES) -Llibft -lft -o pipex

# Rule to build the libft library
$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

# Clean generated files
clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(SRC_DIR)/%.o

# Clean everything
fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)

# Clean and build everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re libft
