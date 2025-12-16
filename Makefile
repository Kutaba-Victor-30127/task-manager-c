CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -Isrc

SRC_DIR := src
DATA_DIR := data

SRC := $(SRC_DIR)/main.c \
       $(SRC_DIR)/task.c \
       $(SRC_DIR)/task_list.c \
       $(SRC_DIR)/task_storage.c\
	   $(SRC_DIR)/input_utils.c

OBJ := $(SRC:.c=.o)

TARGET := task_manager

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# regulă generică pentru .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
