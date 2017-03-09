#include "Terrain.h"
#include "GameWindow.h"
#include "TextureManager.h"
#include "json.hpp"
#include <fstream>
#include "Log.h"

using json = nlohmann::json;

Terrain::Terrain()
{
	TextureManager::load("tex1", "resources/grass01.png");
	TextureManager::load("tex2", "resources/MossyCLiff_diffuse_2.png");
	TextureManager::load("tex3", "resources/mulch-tiled.jpg");
	TextureManager::load("tex1z", "resources/grass01_h.jpg");
	TextureManager::load("tex2z", "resources/MossyCLiff_Height.png");
	TextureManager::load("tex3z", "resources/mulch-heightmap.png");

	TextureManager::get("tex1")->setRepeated(true);
	TextureManager::get("tex2")->setRepeated(true);
	TextureManager::get("tex3")->setRepeated(true);
	TextureManager::get("tex1z")->setRepeated(true);
	TextureManager::get("tex2z")->setRepeated(true);
	TextureManager::get("tex3z")->setRepeated(true);

	shader.loadFromFile("resources/groundShader.frag", sf::Shader::Fragment);
	shader.setUniform("scale", 0.2f);

	shader.setUniform("texture1", *TextureManager::get("tex1"));
	shader.setUniform("texture2", *TextureManager::get("tex2"));
	shader.setUniform("texture3", *TextureManager::get("tex3"));
	shader.setUniform("texture1z", *TextureManager::get("tex1z"));
	shader.setUniform("texture2z", *TextureManager::get("tex2z"));
	shader.setUniform("texture3z", *TextureManager::get("tex3z"));
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
