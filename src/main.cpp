#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <json/json.h>
#include "./particle/particleEngine.h"

int main(){
	Json::Value root;
	Json::Reader reader;
	Json::StyledWriter writer;

	int screenWidth = 1300;
	int screenHeight = 700;
	int maxFPS = 60;
	bool fullscreen = false;

	std::fstream file("./config.json");

	if(!reader.parse(file, root)){
		std::cout<<"Error reading config file:\n"<<reader.getFormatedErrorMessages()<<std::endl;
		return 0;
	}

	try{
		screenWidth = root.get("screenWidth", 1300).asInt();
		screenHeight = root.get("screenHeight", 700).asInt();
		maxFPS = root.get("maxFPS", 60).asInt();
		fullscreen = root.get("fullscreen", false).asBool();
	}
	catch(const std::exception &error){
		std::cerr<<"Exception caught: "<<error.what()<<std::endl;
	}

	file.close();

	file.open("./assets/particleEffects/explosion.json");
	if(!reader.parse(file, root)){
		std::cout<<"Error reading config file:\n"<<reader.getFormatedErrorMessages()<<std::endl;
		return 0;
	}
	file.close();

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "holy particle engine, batman", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar|sf::Style::Close);

	ParticleEngine particleEngine(1000000);
	ParticleEffect explode(root);

	file.open("./assets/particleEffects/ring.json");
	if(!reader.parse(file, root)){
		std::cout<<"Error reading config file:\n"<<reader.getFormatedErrorMessages()<<std::endl;
		return 0;
	}
	file.close();

	ParticleEffect ring(root);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			particleEngine.makeEffect(sf::Mouse::getPosition(window), ring, 30);
			particleEngine.makeEffect(sf::Mouse::getPosition(window), ring, 150);
			// particleEngine.makeEffect(sf::Mouse::getPosition(window), ring, 180);
			particleEngine.makeEffect(sf::Mouse::getPosition(window), explode);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			particleEngine.killAll();
		}

		window.clear();
		particleEngine.updateParticles(&window);
		particleEngine.killParticles();
		window.display();
	}
}
