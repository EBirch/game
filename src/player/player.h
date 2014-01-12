#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Player{
	public:
		sf::Vector2f pos;
		sf::Vector2f force;
		sf::Vector2f vel;
		float mass;
		Player(sf::Vector2f pos);
		void update(float dt);
};

#endif
