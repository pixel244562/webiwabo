CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -I/usr/local/include
LIBS = -L/usr/local/lib64 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = source/main.c source/visual.c source/logic.c source/entrada.c
TARGET = webiwabo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
