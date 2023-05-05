CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lncurses -lcurl

OBJ_DIR = obj
SRC_DIRS = interface curl common
TARGET = typingInstructor

SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS))) typingInstructor.c
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

all: create_obj_dir $(TARGET)

create_obj_dir:
	@mkdir -p $(OBJ_DIR)/interface
	@mkdir -p $(OBJ_DIR)/curl
	@mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)
