#include "./derivative.h"

Derivative::Derivative():
	vel()
	,acc()
{
}

Derivative::Derivative(sf::Vector2f vel, sf::Vector2f acc):
	vel(vel)
	,acc(acc)
{
}

Derivative eval(sf::Vector2f &pos, sf::Vector2f &vel, float dt, Derivative last){
	sf::Vector2f newPos = pos + last.vel * dt;
	sf::Vector2f newVel = vel + last.acc * dt;
	return Derivative(newVel, acceleration(newPos, newVel));
}

sf::Vector2f acceleration(sf::Vector2f pos, sf::Vector2f vel){
	float k = 10;
	float b = 1;
	return -k * pos - b * vel;
}

void rk4(sf::Vector2f &pos, sf::Vector2f &vel, float dt){
	Derivative a = eval(pos, vel, 0.0f, Derivative());
	Derivative b = eval(pos, vel, dt * 0.5f, a);
	Derivative c = eval(pos, vel, dt * 0.5f, b);
	Derivative d = eval(pos, vel, dt, c);

	sf::Vector2f dxdt = 1.0f / 6.0f * (a.vel + 2.0f * (b.vel + c.vel) + d.vel);
	sf::Vector2f dvdt = 1.0f / 6.0f * (a.acc + 2.0f * (b.acc + c.acc) + d.acc);

	pos = pos + dxdt * dt;
	vel = vel + dvdt * dt;
}
