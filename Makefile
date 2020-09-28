
# gcc compiler
CC = gcc

# Compile flags
CFLAGS = -ggdb3 -Wall -O3

# Libs
LIBS = `sdl2-config --cflags --libs`

# Build Target
TARGET = main

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)
