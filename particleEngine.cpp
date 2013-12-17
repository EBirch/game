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

void ParticleEngine::makeEffect(sf::Vector2<int> pos, int numParticles){
	std::uniform_int_distribution<> colorDist(0, 255);
	std::uniform_real_distribution<> velDist(0, 6.2832);
	std::uniform_real_distribution<> speedDist(0.1, 10);
	std::vector<std::future<bool>> futures;
	std::mutex m;
	for(int thread=0;thread<NUMTHREADS;++thread){
		futures.push_back(std::async(std::launch::async, 
			[&]()->bool{
				for(int i = 0;i<numParticles/NUMTHREADS;++i){
					if(particles.size()>=maxParticles){
						return true;
					}
					float angle=velDist(rng);
					auto particle=std::make_shared<Particle>(pos, sf::Vector2<float>(cos(angle), sin(angle)), speedDist(rng), sf::Color(colorDist(rng), colorDist(rng), colorDist(rng)));
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
	displaySize=window->getSize();
	sf::VertexArray points(sf::Points, particles.size());
	int i = 0;
	for(auto part : particles){
		part->vertex.position = part->vertex.position + (part->vel * part->speed);
		++part->lifespan;
		points[i++]=(part->vertex);
	}
	window->draw(points);
	std::cout<<particles.size()<<std::endl;
}

void ParticleEngine::killParticles(){
	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[&](std::shared_ptr<Particle> part){
			return (part->lifespan > 100) || ((part->vertex.position.x < -100 || part->vertex.position.x > displaySize.x + 100) || (part->vertex.position.y < -100 || part->vertex.position.y > displaySize.y + 100));
		}), particles.end());
}

void ParticleEngine::killAll(){
	particles.clear();
}
