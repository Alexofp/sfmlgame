#include "Terrain.h"
#include "GameWindow.h"
#include "TextureManager.h"
#include "json.hpp"
#include <fstream>
#include "Log.h"

using json = nlohmann::json;

Terrain::Terrain()
{
	TextureManager::get("ground_grass")->setRepeated(true);
	TextureManager::get("ground_sand")->setRepeated(true);
	TextureManager::get("ground_dirt")->setRepeated(true);
	TextureManager::get("ground_depth")->setRepeated(true);

	shader.loadFromFile("resources/groundShader.frag", sf::Shader::Fragment);

	shader.setUniform("texture1", *TextureManager::get("ground_grass"));
	shader.setUniform("texture2", *TextureManager::get("ground_sand"));
	shader.setUniform("texture3", *TextureManager::get("ground_dirt"));
	shader.setUniform("texture1z", *TextureManager::get("ground_depth"));
	shader.setUniform("texture2z", *TextureManager::get("ground_depth"));
	shader.setUniform("texture3z", *TextureManager::get("ground_depth"));
}


Terrain::~Terrain()
{
}

void Terrain::draw()
{
	for (auto& part : parts)
	{
		//GameWindow::getInternalHandle().draw(part->ground);

		shader.setUniform("blendtexture", part->texture);
		GameWindow::getInternalHandle().draw(part->ground, &shader);
	}
}

void Terrain::load(std::string folder)
{
	std::ifstream file(folder + "/map.json");
	json jsonData;
	file >> jsonData;

	parts.clear();
	w = jsonData["size"][0].get<int>();
	h = jsonData["size"][1].get<int>();
	tileSize = (float)jsonData["tilesize"].get<int>();

	for (auto& mappart : jsonData["map"])
	{
		int x = mappart["x"].get<int>();
		int y = mappart["y"].get<int>();
		std::string file = mappart["file"].get<std::string>();

		Part* part = new Part();
		part->x = x;
		part->y = y;
		part->ground.setPosition(sf::Vector2f(x*tileSize, y*tileSize));
		part->ground.setSize(sf::Vector2f(tileSize, tileSize));

		part->texture.loadFromFile(folder + "/" + file);

		part->ground.setTexture(&part->texture);

		parts.push_back(std::unique_ptr<Part>(part));
	}
}
