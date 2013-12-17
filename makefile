all: ./src/main.cpp
	g++ -std=c++11 -g ./src/main.cpp ./src/particle/particleEngine.cpp ./src/particle/particle.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -L /usr/local/lib/ ./lib/libjson.so -I ./lib/include
