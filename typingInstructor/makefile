CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -Wno-sizeof-pointer-div 
LDFLAGS = -lncurses -lcurl

OBJ_DIR = obj
SRC_DIRS = interface codeFiles common
TARGET = typingInstructor

SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS))) typingInstructor.c
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

all: create_obj_dir $(TARGET)

create_obj_dir:
	@mkdir -p $(OBJ_DIR)/interface
	@mkdir -p $(OBJ_DIR)/codeFiles
	@mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)
