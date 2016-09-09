# define compiler
CC=g++

# define compiler time flags
CFLAGS=-I. -Wall -g

# define link flags
LINK=

DEPS=
OBJS=main.o

all: | geonorm

clean:
	-rm -f *.o geonorm

#Main.o: Main.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#Compute.o: Compute.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#Song.o: Song.cpp $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

geonorm: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean