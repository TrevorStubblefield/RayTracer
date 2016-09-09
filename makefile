# define compiler
CC=g++

# define compiler time flags
CFLAGS=-I. -Wall -g

# define link flags
LINK=

DEPS=
OBJS=build/main.o

all: | bin/geonorm

clean:
	-rm -f build/* bin/geonorm

#Main.o: Main.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#Compute.o: Compute.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#Song.o: Song.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/geonorm: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean