#include "Skin.h"
#include "json.hpp"
#include <fstream>
#include "TextureManager.h"
using json = nlohmann::json;

Skin::Skin()
{
}


Skin::~Skin()
{
}

void Skin::loadFromFile(std::string path)
{
	parts.clear();

	std::ifstream file(path);
	json jsonData;
	file >> jsonData;

	for (json::iterator it = jsonData["data"].begin(); it != jsonData["data"].end(); ++it)
	{
		std::string boneName = it.key();
		
		for (auto& skinPartJson : jsonData["data"][boneName])
		{
			SkinPart part;
			int z = skinPartJson["z"].get<int>();
			part.z = z;

			for (auto& itemJson: skinPartJson["items"])
			{
				SkinPart::Item item;
				float x = itemJson["x"].get<float>();
				float y = itemJson["y"].get<float>();
				item.shape.setPosition(sf::Vector2f(x,y));
				float w = itemJson["w"].get<float>();
				float h = itemJson["h"].get<float>();
				item.shape.setSize(sf::Vector2f(w, h));
				item.shape.setOrigin(item.shape.getSize()/2.f);
				if (w < 0.f)
					item.shape.setScale(-1.f, item.shape.getScale().y);
				if (h < 0.f)
					item.shape.setScale(item.shape.getScale().x, -1.f);

				float ang = itemJson["ang"].get<float>();
				item.shape.setRotation(ang);

				if (itemJson.find("texture") != itemJson.end())
				{
					item.shape.setTexture( TextureManager::get(itemJson["texture"].get<std::string>()) );

					if (itemJson.find("textureRect") != itemJson.end())
					{
						int x, y, w, h;
						x = itemJson["textureRect"][0].get<int>();
						y = itemJson["textureRect"][1].get<int>();
						w = itemJson["textureRect"][2].get<int>();
						h = itemJson["textureRect"][3].get<int>();

						item.shape.setTextureRect(sf::IntRect(x, y, w, h));
					}
				}

				part.items.push_back(item);
			}
			parts[boneName].push_back(part);
		}
	}
}

std::unordered_map<std::string, std::vector<SkinPart>>& Skin::getParts()
{
	return parts;
}

void Skin::applySkin(Skin otherskin)
{
	for (auto& otherparts : otherskin.getParts())
	{
		parts[otherparts.first] = otherparts.second;
	}
}
