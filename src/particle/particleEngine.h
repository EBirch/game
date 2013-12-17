#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "./particle.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class ParticleEngine{
	public:
		ParticleEngine(int maxParticles);
		void updateParticles(sf::RenderWindow *window=NULL);
		void killParticles();
		void killAll();
		void makeEffect(sf::Vector2<int> pos, int numParticles);

	private:
		std::vector<std::shared_ptr<Particle>> particles;
		int maxParticles;
		std::mt19937 rng;
		sf::Vector2u displaySize;
};

#endif
