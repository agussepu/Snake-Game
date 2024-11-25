# Definición del compilador, las banderas de compilación y las bibliotecas a enlazar
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LIBS = -lSDL2 -lSDL2_ttf    

# Directorios donde se encuentran los archivos fuente, cabeceras y donde se guardarán los archivos objeto
SRCDIR = src
INCDIR = include
BUILD_DIR = build

# Obtención de todos los archivos fuente .c dentro del directorio src
SRCS = $(wildcard $(SRCDIR)/*.c)

# Nombres de los archivos objeto correspondientes
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
EXEC = snake_game # Nombre del ejecutable

# Regla por defecto (cuando solo se ejecuta make)
all: $(EXEC)

# Regla para crear el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)  # Se asegura de enlazar SDL2 y SDL2_ttf

# Regla para compilar los archivos .c en archivos .o
$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@   # Compilación de archivos .c a .o

# Regla para limpiar los archivos generados
clean:
	rm -f $(BUILD_DIR)/*.o $(EXEC)   # Limpiar los archivos compilados y el ejecutable
