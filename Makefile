OBJ=*.cpp

all:
	g++ $(OBJ) -w -I include -L lib -l SDL2
