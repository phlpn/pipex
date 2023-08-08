# Final executable name
NAME = pipex

# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
DFLAGS = -g -DDEBUG

# Directories
SRC_DIR = src
BUILD_DIR = build

# Define the source files
SRC_FILES =	pipex.c labs.c

# Define the path of the sources files
SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES)) 

# Derive object file names from .c files in the build directory
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Rule to build the executables
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from .c files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony target to build the main executable
all: $(NAME)

# Phony target to clean generated files
clean:
	rm -rf $(BUILD_DIR)

# Phony target to remove the executables and object files
fclean: clean
	rm -f $(NAME)
	find . -type f ! \( -name "*.c" -o -name "*.h" -o -name "Makefile" \) -exec rm {} +


# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

.SILENT:
.PHONY: all bonus clean fclean re