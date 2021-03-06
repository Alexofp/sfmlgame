#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2i.h"
#include <vector>
#include <memory>
#include "Vec2f.h"

class Terrain
{
public:
	struct Part
	{
		sf::Texture texture;
		sf::RectangleShape ground;
		int x;
		int y;
	};

	Terrain();
	~Terrain();

	void draw();
	void load(std::string folder);
private:
	//sf::RectangleShape ground;
	sf::Shader shader;
	int w;
	int h;

	std::vector<std::unique_ptr<Part> > parts;

	float tileSize;
};

