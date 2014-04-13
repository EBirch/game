#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "./particle.h"
#include "./particleEffect.h"
#include "./compoundEffect.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class ParticleEngine{
	public:
		ParticleEngine(int maxParticles);
		sf::Color hsv(int hue, float sat, float val);
		void update(sf::RenderWindow *window, int frame);
		void killParticles();
		void killAll();
		void makeEffect(sf::Vector2<int> pos, std::shared_ptr<ParticleEffect> particleEffect, float offset = 0);
		void updateActiveEffects(int frame);
		void addUniformDist(int num, int width, int height);

		std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> activeEffects; //TODO: move this back to private
	private:
		std::vector<std::shared_ptr<Particle>> particles;
		int maxParticles;
		std::mt19937 rng;
		sf::Vector2u displaySize;
};

#endif
