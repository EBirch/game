#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <SFML/System.hpp>

class Derivative{
	public:
		sf::Vector2f vel;
		sf::Vector2f acc;
		Derivative();
		Derivative(sf::Vector2f vel, sf::Vector2f acc);
};

Derivative eval(sf::Vector2f &pos, sf::Vector2f &vel, float dt, Derivative last);
sf::Vector2f acceleration(sf::Vector2f pos, sf::Vector2f vel);
void rk4(sf::Vector2f &pos, sf::Vector2f &vel, float dt);

#endif
