# define compiler
CC=g++

# define compiler time flags
CFLAGS=-I include/ -Wall -g -std=c++11

# define link flags
LINK=

DEPS=include/face.h include/model.h include/util.h include/vertex.h include/camera.h include/scene.h include/color.h include/ray.h include/sphere.h include/surface.h include/light.h
OBJS=build/main.o build/face.o build/model.o build/util.o build/vertex.o build/camera.o build/scene.o build/color.o build/ray.o build/sphere.o build/surface.o build/light.o

all: | bin/raytracer

clean:
	-rm -f build/* bin/raytracer

build/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/raytracer: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean
