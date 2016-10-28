# define compiler
CC=g++

# define compiler time flags
CFLAGS=-I include/ -Wall -g -std=c++11

# define link flags
LINK=

DEPS=include/face.h include/model.h include/util.h include/vertex.h include/camera.h include/scene.h include/pixel.h
OBJS=build/main.o build/face.o build/model.o build/util.o build/vertex.o build/camera.o build/scene.o build/pixel.o

all: | bin/raytracer

clean:
	-rm -f build/* bin/raytracer

build/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/raytracer: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean
