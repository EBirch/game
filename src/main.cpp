#include <SFML/Graphics.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
// #include <boost/foreach.hpp>
#include <unordered_map>
#include <algorithm>
#include "./parseHelpers.h"
#include "./particle/particleEngine.h"

template <class T>
void load(std::string path, std::unordered_map<std::string, std::shared_ptr<T>, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<T>>>> &map);

int main(){
	Json::Value json;

	parse("./config.json", json);

	std::unordered_map<std::string, std::shared_ptr<ParticleEffect>> particleEffects;

	load("./assets/particleEffects", particleEffects);

	int screenWidth = get(json, "screenWidth", 1300);
	int screenHeight = get(json, "screenHeight", 700);
	int maxFPS = get(json, "maxFPS", 60);
	int maxParticles = get(json, "maxParticles", 200000);
	bool fullscreen = get(json, "fullscreen", false);

	ParticleEngine particleEngine(maxParticles);

	auto ring=particleEffects["ring"];
	auto explode=particleEffects["explode"];

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "holy particle engine, batman", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar|sf::Style::Close);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			auto pos = sf::Mouse::getPosition(window);
			particleEngine.makeEffect(pos, particleEffects.at("ring"), -15);
			particleEngine.makeEffect(pos, particleEffects.at("ring"), 40);
			particleEngine.makeEffect(pos, particleEffects.at("explosion"));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			particleEngine.killAll();
		}

		window.clear();
		particleEngine.updateParticles(&window);
		window.display();
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
