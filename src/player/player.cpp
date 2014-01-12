#include "./player.h"
#include "../derivative.h"

Player::Player(sf::Vector2f pos):
	pos(pos)
	,vel()
	,mass(1.0)
{
}

void Player::update(float dt){
	rk4(pos, vel, dt);
}
