CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = chess

SOURCES = main.c 

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
