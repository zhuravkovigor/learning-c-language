CC = clang
# Добавляем путь к заголовочным файлам через -I
CFLAGS = -Wall -Wextra -std=c11 -I/opt/homebrew/include
# Флаги для линковщика: путь к библиотекам (-L), сама либа (-l) и системные фреймворки Apple
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

TARGET = raylib-base-window
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

# Удобно: скомпилировать и сразу запустить
run: all
	./$(TARGET)