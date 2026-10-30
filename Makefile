# Definiciones básicas
CC = gcc
CFLAGS = -Wall -Iinclude
# Librerías necesarias para Raylib en Windows (MinGW)
LIBS = $(shell pkg-config --libs --cflags raylib)

# Archivos fuente y el nombre del ejecutable final
SRC = source/main.c source/visual.c source/logic.c
TARGET = webiwabo.exe

# Regla principal (se ejecuta al escribir solo 'make')
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LIBS)

# Regla para limpiar los archivos ejecutables generados
clean:
	rm -f $(TARGET)
