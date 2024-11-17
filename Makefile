CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LIBS = -lSDL2

SRCDIR = src
INCDIR = include
BUILD_DIR = build

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
EXEC = snake_game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)
