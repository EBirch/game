#include <SFML/Graphics.hpp>
#include <iostream>
#include "./parseHelpers.h"
#include "./particle/particleEngine.h"

int main(){
	Json::Value json;

	parse("./config.json", json);

	int screenWidth = get(json, "screenWidth", 1300);
	int screenHeight = get(json, "screenHeight", 700);
	int maxFPS = get(json, "maxFPS", 60);
	int maxParticles = get(json, "maxParticles", 200000);
	bool fullscreen = get(json, "fullscreen", false);

	ParticleEngine particleEngine(maxParticles);

	parse("./assets/particleEffects/explosion.json", json);
	ParticleEffect explode(json);

	parse("./assets/particleEffects/ring.json", json);
	ParticleEffect ring(json);

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "holy particle engine, batman", fullscreen ? sf::Style::Fullscreen : sf::Style::Titlebar|sf::Style::Close);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			particleEngine.makeEffect(sf::Mouse::getPosition(window), ring, -15);
			particleEngine.makeEffect(sf::Mouse::getPosition(window), ring, 40);
			particleEngine.makeEffect(sf::Mouse::getPosition(window), explode);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			particleEngine.killAll();
		}

		window.clear();
		particleEngine.updateParticles(&window);
		window.display();
	}
}
