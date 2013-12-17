#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Particle{
	public:
		Particle(sf::Vector2<int> pos, sf::Vector2<float> vel, float speed, sf::Color color);
		sf::Vertex vertex;
		sf::Vector2<float> vel;
		float speed;
		int lifespan;
		void update();
};

#endif
