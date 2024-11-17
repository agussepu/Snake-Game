CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lSDL2

SRCS = main.c grid.c snake.c apple.c score.c ranking.c events.c
OBJS = $(SRCS:.c=.o)
EXEC = snake_game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
