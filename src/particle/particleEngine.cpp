#include "./particleEngine.h"
#include <ctime>
#include <iostream>
#include <future>
#include <mutex>
#include <algorithm>
const int NUMTHREADS=8;

ParticleEngine::ParticleEngine(int maxParticles):
	maxParticles(maxParticles)
	,particles()
	,rng(time(NULL))
{
}

void ParticleEngine::makeEffect(sf::Vector2<int> pos, std::shared_ptr<ParticleEffect> particleEffect, float offset){
	std::uniform_int_distribution<> particlesDist(particleEffect->minParticles, particleEffect->maxParticles);
	std::uniform_int_distribution<> lifespanDist(particleEffect->minLifespan, particleEffect->maxLifespan);
	std::uniform_int_distribution<> hueDist(particleEffect->minHue, particleEffect->maxHue);
	std::uniform_real_distribution<> satDist(particleEffect->minSat, particleEffect->maxSat);
	std::uniform_real_distribution<> valDist(particleEffect->minVal, particleEffect->maxVal);
	std::uniform_real_distribution<> speedDist(particleEffect->minSpeed, particleEffect->maxSpeed);
	std::uniform_real_distribution<> velDist(-particleEffect->minAngle, -particleEffect->maxAngle);
	std::uniform_real_distribution<> rotationDist(particleEffect->minRotation, particleEffect->maxRotation);
	std::uniform_real_distribution<> xScaleDist(particleEffect->minXScale, particleEffect->maxXScale);
	std::uniform_real_distribution<> yScaleDist(particleEffect->minYScale, particleEffect->maxYScale);
	int numParticles = particlesDist(rng);
	std::vector<std::future<bool>> futures;
	std::mutex m;
	offset = -(DEG2RAD * offset);
	for(int thread=0;thread<NUMTHREADS;++thread){
		futures.push_back(std::async(std::launch::async, 
			[&]()->bool{
				for(int i = 0;i<numParticles/NUMTHREADS;++i){
					if(particles.size()>=maxParticles){
						return true;
					}
					float angle=velDist(rng);
					auto particle=std::make_shared<Particle>(pos, angle, speedDist(rng), rotationDist(rng), xScaleDist(rng), yScaleDist(rng), lifespanDist(rng), offset, hsv(hueDist(rng), satDist(rng), valDist(rng)));
					{
						std::lock_guard<std::mutex> guard(m);
						particles.push_back(particle);
					}
				}
				return true;
			}));
	}
	for(int i=0;i<futures.size();++i){
		futures[i].get();
	}
}

void ParticleEngine::updateParticles(sf::RenderWindow *window){
	displaySize = window->getSize();
	sf::VertexArray points(sf::Points, particles.size());
	int i = 0;
	for(auto part : particles){
		part->vertex.position = part->vertex.position + (part->vel * part->speed);
		part->angle += part->rotation;
		part->vel = sf::Vector2f((part->xScale * cos(part->angle) * cos(part->offset) - part->yScale * sin(part->angle) * sin(part->offset)), (part->xScale * cos(part->angle) * sin(part->offset) + part->yScale * sin(part->angle) * cos(part->offset)));
		--part->lifespan;
		points[i++]=(part->vertex);
	}
	// std::cout<<particles.size()<<std::endl;
	window->draw(points);
	killParticles();
}

void ParticleEngine::killParticles(){
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[&](std::shared_ptr<Particle> part){
			return (part->lifespan <= 0) || ((part->vertex.position.x < -100 || part->vertex.position.x > displaySize.x + 100) || (part->vertex.position.y < -100 || part->vertex.position.y > displaySize.y + 100));
		}), particles.end());
}

void ParticleEngine::killAll(){
	particles.clear();
}

sf::Color ParticleEngine::hsv(int hue, float sat, float val){
	hue %= 360;
	while(hue<0){
		hue += 360;
	}
	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));
	switch(h){
		default:
		case 0:
		case 6: return sf::Color(val * 255, t * 255, p * 255);
		case 1: return sf::Color(q * 255, val * 255, p * 255);
		case 2: return sf::Color(p * 255, val * 255, t * 255);
		case 3: return sf::Color(p * 255, q * 255, val * 255);
		case 4: return sf::Color(t * 255, p * 255, val * 255);
		case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}
