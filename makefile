LIBS = -lsfml-graphics -lsfml-window -lsfml-system ./lib/libjson.so
LIBPATH = -L /usr/local/lib/
INCLUDE = -I ./lib/include
OBJECTS = particle.o particleEngine.o particleEffect.o

all: ./src/main.cpp $(OBJECTS)
	g++ -std=c++11 -g $(OBJECTS) -O3 ./src/main.cpp ./src/parseHelpers.cpp $(LIBS) $(LIBPATH) $(INCLUDE) -o main.o

particle.o: ./src/particle/particle.cpp
	g++ -std=c++11 -c -O3 ./src/particle/particle.cpp

particleEngine.o: ./src/particle/particleEngine.cpp
	g++ -std=c++11 -c -O3 ./src/particle/particleEngine.cpp $(INCLUDE)

particleEffect.o: ./src/particle/particleEffect.cpp
	g++ -std=c++11 -c -O3 ./src/particle/particleEffect.cpp $(INCLUDE)

clean:
	rm *.o
	make all
