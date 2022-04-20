OBJ=*.cpp

all:
	g++ $(OBJ) -w -std=c++17 -I include -L lib -l SDL2
