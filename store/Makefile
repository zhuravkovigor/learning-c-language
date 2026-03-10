CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = store

# 1. Функция wildcard находит ВСЕ файлы .c в текущей директории
SRCS = $(wildcard *.c)

# 2. Функция patsubst превращает список .c файлов в список .o файлов
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

dev: all
	./$(TARGET)