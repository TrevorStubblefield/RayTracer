# define compiler
CC=g++

# define compiler time flags
CFLAGS=-I include/ -Wall -g

# define link flags
LINK=

DEPS=include/face.h include/model.h include/util.h include/vertex.h
OBJS=build/main.o build/face.o build/model.o build/util.o build/vertex.o

all: | bin/geonorm

clean:
	-rm -f build/* bin/geonorm

build/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/geonorm: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean