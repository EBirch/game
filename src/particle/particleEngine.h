#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "./particle.h"
#include "./particleEffect.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class ParticleEngine{
	public:
		ParticleEngine(int maxParticles);
		sf::Color hsv(int hue, float sat, float val);
		void updateParticles(sf::RenderWindow *window = NULL);
		void killParticles();
		void killAll();
		void makeEffect(sf::Vector2<int> pos, ParticleEffect particleEffect, int rotate = 0);

	private:
		std::vector<std::shared_ptr<Particle>> particles;
		int maxParticles;
		std::mt19937 rng;
		sf::Vector2u displaySize;
};

#endif
