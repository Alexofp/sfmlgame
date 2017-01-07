#pragma once
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	static void load(std::string name, std::string path);
	static const sf::Texture* get(std::string name);
	static void loadFromFile(std::string path);
protected:
private:
	static TextureManager& getInstance();
	std::unordered_map<std::string, sf::Texture> data;
};

