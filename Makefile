SHELL = /bin/sh
FLAGS = -Wall -g
CC = g++

all:    dynpipe TwoPipesThreeChildren TwoPipesTwoChildren

dynpipe:     dynpipe.cpp
	$(CC) $(FLAGS) -o $@ dynpipe.cpp

TwoPipesThreeChildren :     TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp

TwoPipesThreeChildren :     TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

clean:
	rm dynpipe TwoPipesThreeChildren TwoPipesTwoChildren
