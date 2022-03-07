NAME = cluster
INCLUDE = -Iinclude
HEADER = include/cluster.h

SRC_DIR = srcs
BUILD_DIR = obj
SRC_EXT = c
OBJ_EXT = o

SOURCES := $(shell find $(SRC_DIR) -type f -name "*.$(SRC_EXT)")
OBJS    := $(SOURCES:.$(SRC_EXT)=.$(OBJ_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(OBJS))


# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
ifdef DEBUG
 CFLAGS += -g3
endif
ifdef LEAKS
 CFLAGS += -g3 -fsanitize=address
endif

SHELL := /bin/bash
export SHELL
export DEBUG

all: directories $(NAME)

directories:
	@mkdir -p $(BUILD_DIR)

$(NAME): $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(PINK)Done building $(NAME) $(RESET)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(INCLUDE) $^ -o $@

client: client.o
	$(CC) $(CFLAGS) client.o -o $@

clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

dirs:
	@mkdir $(patsubst %, $(PATH_OBJ)/%, $(DIRS)) $(patsubst %, bin/%, $(DIRS))
