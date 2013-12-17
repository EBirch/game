all: main.cpp
	g++ -std=c++11 -g main.cpp particleEngine.cpp particle.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -L /usr/local/lib/ ./lib/libjson.so
