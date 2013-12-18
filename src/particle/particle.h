#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Particle{
	public:
		Particle(sf::Vector2<int> pos, float angle, float speed, float rotation, int lifespan, sf::Color color);
		sf::Vertex vertex;
		sf::Vector2<float> vel;
		float angle;
		float rotation;
		float speed;
		int lifespan;
};

#endif
