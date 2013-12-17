#include "./particle.h"
#include <SFML/System.hpp>

Particle::Particle(sf::Vector2<int> pos, sf::Vector2<float> vel, float speed, sf::Color color):
	vel(vel)
	,speed(speed)
	,lifespan(0)
	,vertex(sf::Vector2f(pos.x, pos.y), color)
{
}
