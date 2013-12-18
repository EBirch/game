#include "./particle.h"
#include <SFML/System.hpp>

Particle::Particle(sf::Vector2<int> pos, float angle, float speed, float rotation, int lifespan, sf::Color color):
	angle(angle)
	,speed(speed)
	,lifespan(lifespan)
	,vertex(sf::Vector2f(pos.x, pos.y), color)
	,vel(cos(angle), sin(angle))
	,rotation(rotation)
{
}
