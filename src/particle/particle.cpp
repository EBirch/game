#include "./particle.h"
#include <SFML/System.hpp>

Particle::Particle(sf::Vector2<int> pos, float angle, float speed, float rotation, float xScale, float yScale, int lifespan, float offset, sf::Color color):
	angle(angle)
	,speed(speed)
	,lifespan(lifespan)
	,vertex(sf::Vector2f(pos.x, pos.y), color)
	,vel((xScale * cos(angle) * cos(offset) - yScale * sin(angle) * sin(offset)), (xScale * cos(angle) * sin(offset) + yScale * sin(angle) * cos(offset)))
	,rotation(rotation)
	,xScale(xScale)
	,yScale(yScale)
	,offset(offset)
{
}
