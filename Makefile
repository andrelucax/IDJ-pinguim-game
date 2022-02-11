CC := g++
CFLAGS := -Wall
LSDLFLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer

SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/main $(LSDLFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc $(LSDLFLAGS)

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

run:
	bin/main
