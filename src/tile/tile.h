#ifndef TILE_H
#define TILE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Tile{
	public:
		sf::Vertex pos;
		bool solid;
		int height;
		int width;

		Tile(sf::Vector2f pos, int height, int width);
};

#endif
