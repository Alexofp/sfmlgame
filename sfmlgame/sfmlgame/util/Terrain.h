#pragma once
#include <SFML/Graphics.hpp>

class Terrain
{
public:
	Terrain();
	~Terrain();

	void draw();
private:
	sf::RectangleShape ground;
	sf::Shader shader;
};

