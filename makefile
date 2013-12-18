LIBS = -lsfml-graphics -lsfml-window -lsfml-system ./lib/libjson.so
LIBPATH = -L /usr/local/lib/
INCLUDE = -I ./lib/include
OBJECTS = particle.o particleEngine.o particleEffect.o

all: ./src/main.cpp $(OBJECTS)
	g++ -std=c++11 -g $(OBJECTS) ./src/main.cpp $(LIBS) $(LIBPATH) $(INCLUDE) -o main 

particle.o: ./src/particle/particle.cpp
	g++ -std=c++11 -c ./src/particle/particle.cpp

particleEngine.o: ./src/particle/particleEngine.cpp
	g++ -std=c++11 -c ./src/particle/particleEngine.cpp $(INCLUDE)

particleEffect.o: ./src/particle/particleEffect.cpp
	g++ -std=c++11 -c ./src/particle/particleEffect.cpp $(INCLUDE)
