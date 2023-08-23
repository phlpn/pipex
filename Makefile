# Final executable name
NAME 		= pipex

# Compiler and compiler flags
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -Iinclude -Ilibft
DFLAGS 		= -g -DDEBUG -fsanitize=address

# Directories
SRC_DIR 	= src
BUILD_DIR 	= build
LIBFT_DIR 	= libft

# Define the source files
SRC_FILES 	= pipex.c utils.c

# Define the path of the sources files
SRCS 		= $(addprefix $(SRC_DIR)/,$(SRC_FILES)) 

# Derive object file names from .c files in the build directory
OBJS 		= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Rule to build the executables
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build the object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the libft library
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

# Phony target to build the libft library
libft:
	make -C $(LIBFT_DIR)

# Phony target to build the main executable and the libft library
all: libft $(NAME)

# Phony target to clean generated files
clean:
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

# Phony target to remove the executables, object files, and libft library
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -f *.txt

# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

.SILENT:
.PHONY: all libft clean fclean re debug
