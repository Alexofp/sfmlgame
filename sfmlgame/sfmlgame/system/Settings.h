#pragma once
#include "json.hpp"
#include "Vec2f.h"
#include "Vec2i.h"

using json = nlohmann::json;

class Settings
{
public:
	Settings();
	~Settings();

	static void setInt(std::string category, std::string name, int value);
	static int getInt(std::string category, std::string name, int def = 0);

	static void setBool(std::string category, std::string name, bool value);
	static int getBool(std::string category, std::string name, bool def = false);

	static void setVec2i(std::string category, std::string name, Vec2i value);
	static Vec2i getVec2i(std::string category, std::string name, Vec2i def = Vec2i(0,0));

	static void save();
	static void load();


private:
	json jsonData;

	static void defaults();
	static Settings& get();
};

