#ifndef PARTICLE_H
#define PARTICLE_H

#define DEG2RAD 0.01745329251994
#define SQRT2 1.41421356237309

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Particle{
	public:
		Particle(sf::Vector2<int> pos, float angle, float speed, float rotation, float xScale, float yScale, int lifespan, float offset, sf::Color color);
		sf::Vertex vertex;
		sf::Vector2<float> vel;
		float angle;
		float rotation;
		float speed;
		float xScale;
		float yScale;
		float offset;
		int lifespan;
};

#endif
