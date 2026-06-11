CC = gcc
CFLAGS = -Wall -Wextra -g

SOURCES = main.c board.c initialize.c kingsafety.c movegen.c playmove.c printAllMoves.c turn.c
TARGET = chess

OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
