# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Iinc

# Directories
SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj
BIN_DIR := bin

# Files
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET  := $(BIN_DIR)/pathfinder

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if missing
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Cleanup
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
