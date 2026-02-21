CC = gcc
CFLAGS = -pedantic -Werror -Wall -Wextra -Wvla -I./include/
LDFLAGS = -lm -lSDL2 -lSDL2_image

SRC_DIR = src

SRC = $(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(SRC:.c=.o) 
TARGET = cube

.PHONY: cube clean all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

debug: CFLAGS+=-g -fsanitize=address
debug: LDFLAGS+=-g
debug: all

clean:
	$(RM) -r $(TARGET) $(OBJ)
