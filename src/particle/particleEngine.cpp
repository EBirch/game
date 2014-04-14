#include "./particleEngine.h"
#include <ctime>
#include <iostream>
#include <future>
#include <mutex>
#include <algorithm>
const int NUMTHREADS=1;

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
					auto particle=std::make_shared<Particle>(pos, angle, speedDist(rng), rotationDist(rng), xScaleDist(rng), yScaleDist(rng), lifespanDist(rng), offset, hsv(hueDist(rng), satDist(rng), valDist(rng)), particleEffect->physics, true);
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

void ParticleEngine::update(sf::RenderWindow *window, int frame){
	displaySize = window->getSize();
	sf::VertexArray points(sf::Points, particles.size());
	int i = 0;
	for(auto part : particles){
		part->vertex.position = part->vertex.position + (part->vel * part->speed);
		if(part->vertex.position.x > displaySize.x){
			part->vertex.position.x = displaySize.x;
			part->vel.x *= -1;
		}
		if(part->vertex.position.x < 0){
			part->vertex.position.x = 0;
			part->vel.x *= -1;
		}
		if(part->vertex.position.y > displaySize.y){
			part->vertex.position.y = displaySize.y;
			part->vel.y *= -1;
		}
		if(part->vertex.position.y < 0){
			part->vertex.position.y = 0;
			part->vel.y *= -1;
		}
		part->angle += part->rotation;
		if(part->angular){
			part->vel = sf::Vector2f((part->xScale * cos(part->angle) * cos(part->offset) - part->yScale * sin(part->angle) * sin(part->offset)), (part->xScale * cos(part->angle) * sin(part->offset) + part->yScale * sin(part->angle) * cos(part->offset)));
		}
		if(part->physics){
			part->vel = sf::Vector2f(part->vel.x * 0.995, part->vel.y * 0.995); //TODO: allow for variable friction
			part->speed *= 0.999;
		}
		--part->lifespan;
		points[i++]=(part->vertex);
	}
	// std::cout<<particles.size()<<std::endl;
	window->draw(points);
	killParticles();
	updateActiveEffects(frame);
}

void ParticleEngine::updateActiveEffects(int frame){
	std::for_each(activeEffects.begin(), activeEffects.end(),
		[&](std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>> compound){
			auto effect = std::get<0>(compound)->effectMap.find(frame - std::get<1>(compound));
			if(effect != std::get<0>(compound)->effectMap.end()){
				auto pos = std::get<2>(compound);
				std::for_each(effect->second.begin(), effect->second.end(),
					[&](std::tuple<std::shared_ptr<ParticleEffect>, int, int, float> timestep){
						makeEffect(sf::Vector2<int>(pos.x + std::get<1>(timestep), pos.y + std::get<2>(timestep)), std::get<0>(timestep), std::get<3>(timestep));
					});
			}
		});
	activeEffects.erase(std::remove_if(activeEffects.begin(), activeEffects.end(),
		[&](std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>> compound){
			return (frame - std::get<1>(compound)) > std::get<0>(compound)->end;
		}), activeEffects.end());
}

void ParticleEngine::addUniformDist(int num, int width, int height){
	double dist = sqrt((double)(width * height) / num);
	std::uniform_int_distribution<> hueDist(0, 360);
	std::uniform_real_distribution<> satDist(0, 1);
	std::uniform_real_distribution<> valDist(0, 1);
	// std::cout<<num<<": "<<width<<", "<<height<<": "<<dist<<std::endl;
	for(double y = 0; y < height; y += dist){
		for(double x = 0; x < width; x += dist){
			particles.push_back(std::make_shared<Particle>(sf::Vector2<int>((int)x, (int)y), 0, 1, 0, 1, 1, 300000000, 0, hsv(hueDist(rng), satDist(rng), valDist(rng)), true, false));
		}
	}
}

void ParticleEngine::applyForce(sf::Vector2<int> pos, float force, float radius){
	for(auto part : particles){
		if(!part->physics){
			continue;
		}
		double dist = radius - sqrt(pow(part->vertex.position.x - pos.x, 2) + pow(part->vertex.position.y - pos.y, 2));
		if(dist <= 0){
			continue;
		}
		// std::cout<<"doing thing\n";
		part->angle = atan((double)(part->vertex.position.y - pos.y) / (part->vertex.position.x - pos.x)) + part->rotation;
		auto temp = sf::Vector2f(part->vertex.position.x - pos.x, part->vertex.position.y - pos.y);
		double scale = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
		temp = sf::Vector2f(temp.x / scale, temp.y / scale);
		// part->vel = sf::Vector2f((part->xScale * cos(part->angle) * cos(part->offset) - part->yScale * sin(part->angle) * sin(part->offset)), (part->xScale * cos(part->angle) * sin(part->offset) + part->yScale * sin(part->angle) * cos(part->offset)));
		part->vel = sf::Vector2f(temp.x * (force * (dist / radius)), temp.y * (force * (dist / radius)));
		// part->speed *= 1 + 0.025 * (dist / radius);
		// part->vertex.position = part->vertex.position + (part->vel * part->speed);
	}
}

void ParticleEngine::killParticles(){
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[&](std::shared_ptr<Particle> part){
			return (part->lifespan <= 0) || ((part->vertex.position.x < -100 || part->vertex.position.x > displaySize.x + 100) || (part->vertex.position.y < -100 || part->vertex.position.y > displaySize.y + 100));
		}), particles.end());
}

void ParticleEngine::killAll(){
	particles.clear();
	activeEffects.clear();
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
