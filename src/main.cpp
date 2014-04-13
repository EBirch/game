#include <SFML/Graphics.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <unordered_map>
#include <algorithm>
#include "./parseHelpers.h"
#include "./particle/particleEngine.h"
#include "./particle/compoundEffect.h"
#include "./player/player.h"

template <class T>
void load(std::string path, std::unordered_map<std::string, std::shared_ptr<T>, std::hash<std::string>, std::equal_to<std::string>, std::allocator<std::pair<std::string const, std::shared_ptr<T>>>> &map);

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


	ParticleEngine particleEngine(maxParticles);
	// Player player(sf::Vector2f(screenWidth / 2, screenHeight / 2));

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "holy particle engine, batman", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar|sf::Style::Close);

	int frame = 0; //change to dt
	bool active = false;

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//change this to an input handler later
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !active){
			active = true;
			// particleEngine.activeEffects.push_back(std::make_tuple(compoundEffects.at("second"), frame, sf::Mouse::getPosition(window)));
			particleEngine.addUniformDist(100000, screenWidth, screenHeight);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			active = false;
			particleEngine.killAll();
		}

		window.clear();
		particleEngine.update(&window, frame); //rename to update?
		// player.update();
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
