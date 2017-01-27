#pragma once
#include "TextureManager.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class BlueprintBackground
{
public:
	BlueprintBackground();
	~BlueprintBackground();

	void draw();
private:
	void update();

	sf::VertexArray grid;
	sf::Texture* texture;
	sf::Vector2f pos1;
	sf::Vector2f pos2;
	sf::Vector2i ipos1;
	sf::Vector2i ipos2;

	sf::RectangleShape xline;
	sf::RectangleShape yline;
};

