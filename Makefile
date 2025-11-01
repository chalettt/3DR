CC = gcc
CFLAGS = -pedantic -Werror -Wall -Wextra -Wvla
LDFLAGS = -lm -lSDL2 -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

TARGET = cube

.PHONY: cube clean all

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

debug: CFLAGS+=-g -fsanitize=address
debug: LDFLAGS+=-g
debug: all

clean:
	$(RM) -r $(TARGET) $(OBJ_DIR)
