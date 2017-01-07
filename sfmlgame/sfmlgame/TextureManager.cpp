#include "TextureManager.h"
#include <fstream>

TextureManager::TextureManager()
{
	//ctor
}

TextureManager::~TextureManager()
{
	//dtor
}

TextureManager& TextureManager::getInstance()
{
	static TextureManager t;
	return t;
}

void TextureManager::load(std::string name, std::string path)
{
	sf::Texture t;
	t.loadFromFile(path);
	getInstance().data[name] = t;
}

const sf::Texture* TextureManager::get(std::string name)
{
	return &getInstance().data.at(name);
}

void TextureManager::loadFromFile(std::string path)
{
	std::ifstream input(path);

	while (!input.eof())
	{
		std::string name, path;
		input >> name >> path;
		load(name, path);
	}
}