CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 -g
LDFLAGS = -lm

SRC = src/main.c src/image.c
OBJ = $(SRC:.c=.o)
TARGET = fractal_gen

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) *.pgm