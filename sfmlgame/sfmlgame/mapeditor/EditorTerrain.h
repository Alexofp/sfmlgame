#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2i.h"
#include <vector>
#include <memory>
#include "Vec2f.h"

class EditorTerrain
{
public:
	struct Part
	{
		sf::RenderTexture texture;
		sf::RectangleShape ground;
		int x;
		int y;
	};

	EditorTerrain();
	~EditorTerrain();

	void resetSize(Vec2i size, float tilesize);

	void drawOnMap(Vec2f pos, float radius, sf::Color color);
	void save(std::string folder);
	void load(std::string folder);

	void draw();
private:
	//sf::RectangleShape ground;
	sf::Shader shader;
	int w;
	int h;
	
	std::vector<std::unique_ptr<Part> > parts;

	float tileSize;
};

