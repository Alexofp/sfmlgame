#include "EditorTerrain.h"
#include "GameWindow.h"
#include "TextureManager.h"
#include "json.hpp"
#include <fstream>
#include "Log.h"

using json = nlohmann::json;

EditorTerrain::EditorTerrain()
{
	tileSize = 6000;

	TextureManager::load("tex1", "resources/grass01.png");
	TextureManager::load("tex2", "resources/MossyCLiff_diffuse_2.png");
	TextureManager::load("tex3", "resources/mulch-tiled.jpg");
	TextureManager::load("tex1z", "resources/grass01_h.jpg");
	TextureManager::load("tex2z", "resources/MossyCLiff_Height.png");
	TextureManager::load("tex3z", "resources/mulch-heightmap.png");

	//TextureManager::load("blend", "resources/blendmap.png");

	TextureManager::get("tex1")->setRepeated(true);
	TextureManager::get("tex2")->setRepeated(true);
	TextureManager::get("tex3")->setRepeated(true);
	TextureManager::get("tex1z")->setRepeated(true);
	TextureManager::get("tex2z")->setRepeated(true);
	TextureManager::get("tex3z")->setRepeated(true);
	//ground.setTexture(TextureManager::get("tex1"));

	shader.loadFromFile("resources/groundShader.frag", sf::Shader::Fragment);
	shader.setUniform("scale", 0.2f);

	shader.setUniform("texture1", *TextureManager::get("tex1"));
	shader.setUniform("texture2", *TextureManager::get("tex2"));
	shader.setUniform("texture3", *TextureManager::get("tex3"));
	shader.setUniform("texture1z", *TextureManager::get("tex1z"));
	shader.setUniform("texture2z", *TextureManager::get("tex2z"));
	shader.setUniform("texture3z", *TextureManager::get("tex3z"));
	//shader.setUniform("blendtexture", *TextureManager::get("blend"));

	TextureManager::load("editorTerrain_gradient", "resources/gradient.png");
}


EditorTerrain::~EditorTerrain()
{
}

void EditorTerrain::resetSize(Vec2i size, float tilesize)
{
	w = size.x;
	h = size.y;
	tileSize = tilesize;

	parts.clear();

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			Part* part = new Part();
			part->x = x;
			part->y = y;
			part->ground.setPosition(sf::Vector2f(x*tileSize, y*tileSize));
			part->ground.setSize(sf::Vector2f(tileSize, tileSize));

			part->texture.create(1024, 1024);
			part->texture.clear(sf::Color::Red);
			
			sf::View view;
			view.setSize(sf::Vector2f(tileSize, tileSize));
			view.setCenter(sf::Vector2f(tileSize/2.f + x*tileSize, tileSize/2.f + y*tileSize));
			part->texture.setView(view);

			part->ground.setTexture(&part->texture.getTexture());

			parts.push_back(std::unique_ptr<Part>(part));
		}
	}
}

void EditorTerrain::drawOnMap(Vec2f pos, float radius, sf::Color color)
{
	sf::RectangleShape shape;
	shape.setFillColor(color);
	shape.setOrigin(radius, radius);
	shape.setSize(sf::Vector2f(radius * 2, radius * 2));
	shape.setPosition(pos.toSFMLVec());
	shape.setTexture(TextureManager::get("editorTerrain_gradient"));

	for (auto& part : parts)
	{
		part->texture.draw(shape);
		part->texture.display();
	}
}

void EditorTerrain::save(std::string folder)
{
	json jsonData;
	jsonData["size"][0] = w;
	jsonData["size"][1] = h;
	jsonData["tilesize"] = tileSize;

	jsonData["map"] = json::array();
	int i = 0;
	for (auto& part : parts)
	{
		json jsonPart;
		jsonPart["x"] = part->x;
		jsonPart["y"] = part->y;
		jsonPart["file"] = "textures/map"+std::to_string(i)+".png";
		i++;

		sf::Image image = part->texture.getTexture().copyToImage();
		image.saveToFile(folder+"/"+jsonPart["file"].get<std::string>());
		jsonData["map"].push_back(jsonPart);
		Log::debug("Saved image " + folder + "/" + jsonPart["file"].get<std::string>());
	}
	std::ofstream file(folder + "/map.json");
	file << std::setw(4) << jsonData;
}

void EditorTerrain::load(std::string folder)
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

		sf::Texture maptexture;
		maptexture.loadFromFile(folder + "/" + file);

		part->texture.create(1024, 1024);
		part->texture.clear(sf::Color::Red);
		sf::RectangleShape shape;
		shape.setTexture(&maptexture);
		shape.setSize(sf::Vector2f(1024, 1024));
		part->texture.draw(shape);
		part->texture.display();

		sf::View view;
		view.setSize(sf::Vector2f(tileSize, tileSize));
		view.setCenter(sf::Vector2f(tileSize / 2.f + x*tileSize, tileSize / 2.f + y*tileSize));
		part->texture.setView(view);

		part->ground.setTexture(&part->texture.getTexture());

		parts.push_back(std::unique_ptr<Part>(part));
	}
}

void EditorTerrain::draw()
{
	for (auto& part : parts)
	{
		//GameWindow::getInternalHandle().draw(part->ground);
		
		shader.setUniform("blendtexture", part->texture.getTexture());
		GameWindow::getInternalHandle().draw(part->ground, &shader);
	}
}
