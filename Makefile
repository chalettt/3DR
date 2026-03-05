CC = gcc
CFLAGS = -pedantic -Werror -Wall -Wextra -Wvla -I./include/
LDFLAGS = -lm -lSDL2

SRC_DIR = src

SRC = $(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(SRC:.c=.o) 
TARGET = 3DR

.PHONY: cube clean all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

doc:
	doxygen Doxyfile

debug: CFLAGS=-g -fsanitize=address -I./include/
debug: LDFLAGS+=-g
debug: all

clean:
	$(RM) -r $(TARGET) $(OBJ)
