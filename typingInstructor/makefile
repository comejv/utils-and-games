CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

OBJ_DIR = obj
SRC_DIR = interface
TARGET = typingInstructor

_OBJ = userInterface.o typingInstructor.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

all: create_obj_dir $(TARGET) clean

create_obj_dir:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o
	rmdir $(OBJ_DIR)
