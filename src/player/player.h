#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Player{
	public:
		sf::Vector2f pos;
		sf::Vector2f movement;
		sf::Vector2f acceleration;
		Player(sf::Vector2f pos);
};

#endif
