CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LIBS = -lSDL2 -lSDL2_ttf   

SRCDIR = src
INCDIR = include
BUILD_DIR = build

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
EXEC = snake_game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)  # Se asegura de enlazar SDL2 y SDL2_ttf

$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@   # Compilación de archivos .c a .o

clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)   # Limpiar los archivos compilados y el ejecutable
