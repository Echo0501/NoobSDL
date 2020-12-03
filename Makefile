
# gcc compiler
CC := gcc

# Compile flags
CFLAGS := -ggdb3 -Wall


# Build Target
TARGET := main
GRAPHC := NoobSDL


# Libs
GRAPHCLIBS := `sdl2-config --cflags --libs`
ALLLIBS := $(GRAPHCLIBS)


all: $(TARGET)

$(TARGET): main.o $(GRAPHC).o
	$(CC) $(CFLAGS) -o $@ $^ $(ALLLIBS)

main.o: main.c $(GRAPHC).h
	$(CC) $(CFLAGS) -c $< $(ALLLIBS)

$(GRAPHC).o: $(GRAPHC).c $(GRAPHC).h
	$(CC) $(CFLAGS) -c $< $(GRAPHCLIBS)

clean:
	rm -f *.o
