#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

struct SkinPart
{
	struct Item
	{
		sf::RectangleShape shape;
	};

	std::vector<Item> items;
	int z;
};

class Skin
{
public:
	Skin();
	~Skin();

	void loadFromFile(std::string path);
	std::unordered_map<std::string, std::vector<SkinPart> >& getParts();
private:
	std::unordered_map<std::string, std::vector<SkinPart> > parts;
};

