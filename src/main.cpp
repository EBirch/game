#include <SFML/Graphics.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <unordered_map>
#include <algorithm>
#include "./parseHelpers.h"
#include "./particle/particleEngine.h"
#include "./particle/compoundEffect.h"

template <class T>
void load(std::string path, std::unordered_map<std::string, std::shared_ptr<T>, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<T>>>> &map);
void updateActiveEffects(ParticleEngine &particleEngine, std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> &activeEffects, int frame);
void killParticles(ParticleEngine &particleEngine, std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> &activeEffects);

std::unordered_map<std::string, std::shared_ptr<ParticleEffect>> particleEffects;
std::unordered_map<std::string, std::shared_ptr<CompoundEffect>> compoundEffects;

int main(){
	Json::Value json;

	parse("./config.json", json);

	load("./assets/particleEffects", particleEffects);
	load("./assets/compoundEffects", compoundEffects);

	int screenWidth = get(json, "screenWidth", 1300);
	int screenHeight = get(json, "screenHeight", 700);
	int maxFPS = get(json, "maxFPS", 60);
	int maxParticles = get(json, "maxParticles", 200000);
	bool fullscreen = get(json, "fullscreen", false);

	std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> activeEffects;

	ParticleEngine particleEngine(maxParticles);

	auto ring=particleEffects["ring"];
	auto explode=particleEffects["explode"];

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "holy particle engine, batman", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar|sf::Style::Close);

	int frame = 0;

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			activeEffects.push_back(std::make_tuple(compoundEffects.at("second"), frame, sf::Mouse::getPosition(window)));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			killParticles(particleEngine, activeEffects);
		}

		window.clear();
		updateActiveEffects(particleEngine, activeEffects, frame);
		particleEngine.updateParticles(&window);
		window.display();
		++frame;
	}
}

template <class T>
void load(std::string path, std::unordered_map<std::string, std::shared_ptr<T>, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<T>>>> &map){
	Json::Value json;
	std::for_each(boost::filesystem::directory_iterator(boost::filesystem::path(path)), boost::filesystem::directory_iterator(),
		[&](boost::filesystem::path file){
			parse(file.string(), json);
			map.insert(std::make_pair(file.stem().string(), std::make_shared<T>(json)));
		});
}

void updateActiveEffects(ParticleEngine &particleEngine, std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> &activeEffects, int frame){
	std::for_each(activeEffects.begin(), activeEffects.end(),
		[&](std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>> compound){
			auto effect = std::get<0>(compound)->effectMap.find(frame - std::get<1>(compound));
			if(effect != std::get<0>(compound)->effectMap.end()){
				auto pos = std::get<2>(compound);
				std::for_each(effect->second.begin(), effect->second.end(),
					[&](std::tuple<std::shared_ptr<ParticleEffect>, int, int, float> timestep){
						particleEngine.makeEffect(sf::Vector2<int>(pos.x + std::get<1>(timestep), pos.y + std::get<2>(timestep)), std::get<0>(timestep), std::get<3>(timestep));
					});
			}
		});
	activeEffects.erase(std::remove_if(activeEffects.begin(), activeEffects.end(),
		[&](std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>> compound){
			return (frame - std::get<1>(compound)) > std::get<0>(compound)->end;
		}), activeEffects.end());
}

void killParticles(ParticleEngine &particleEngine, std::vector<std::tuple<std::shared_ptr<CompoundEffect>, int, sf::Vector2<int>>> &activeEffects){
	particleEngine.killAll();
	activeEffects.clear();
}
