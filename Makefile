# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/24 13:17:37 by alexphil          #+#    #+#              #
#    Updated: 2023/08/24 16:04:27 by alexphil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME 		= 	pipex

# Compiler and compiler flags
CC			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g -Iinclude
DFLAGS      =   -fsanitize=address -g

# Directories for source files, object files, and the libft library
SRC_DIR 	= 	src
BUILD_DIR 	= 	build
LIBFT_DIR 	= 	libft

# Define the source files
SRC_FILES 	= 	pipex.c utils.c

# Define the path of the sources files 
SRC 		= 	$(addprefix $(SRC_DIR)/,$(SRC_FILES)) 

# Derive object file names from .c files in the build directory
OBJS 		= 	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Rule to build the objects from the sources 
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the libft library
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

# Rule to build the executable from the objects and the libft library
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^

# Phony target to build the libft library
libft:
	make -C $(LIBFT_DIR)

# Phony target to build the libft library and the executable
all: libft $(NAME)

# Phony target to clean the object files
clean:
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

# Phony target to remove the executable, build objects and .txt files
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -f *.txt
	rm -rf *.dSYM

# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: re

# Phony target to run the executable with valgrind
leaks: debug
	valgrind --leak-check=full ./$(NAME) infile.txt "ls -l" "wc -l" outfile.txt

# --silent flag disable echoing of commands on MacOS and Linux
MAKEFLAGS += --silent

# Phony targets for make
.PHONY: libft all clean fclean re debug leaks
