#include "Settings.h"
#include <filesystem>
#include <fstream>


using namespace std::experimental;

void Settings::defaults()
{
	setVec2i("window", "size", Vec2i(800, 700));
	setBool("window", "fullscreen", false);
	setBool("render", "debug", true);
}

Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::setInt(std::string category, std::string name, int value)
{
	Settings& settings = get();
	settings.jsonData[category][name] = value;
}

int Settings::getInt(std::string category, std::string name, int def)
{
	Settings& settings = get();
	 if (settings.jsonData[category].find(name) == settings.jsonData[category].end())
		 return def;
	return settings.jsonData[category][name].get<int>();
}

void Settings::setBool(std::string category, std::string name, bool value)
{
	Settings& settings = get();
	settings.jsonData[category][name] = value;
}

int Settings::getBool(std::string category, std::string name, bool def)
{
	Settings& settings = get();
	if (settings.jsonData[category].find(name) == settings.jsonData[category].end())
		return def;
	return settings.jsonData[category][name].get<bool>();
}

void Settings::setVec2i(std::string category, std::string name, Vec2i value)
{
	Settings& settings = get();
	settings.jsonData[category][name][0] = value.x;
	settings.jsonData[category][name][1] = value.y;
}

Vec2i Settings::getVec2i(std::string category, std::string name, Vec2i def)
{
	Settings& settings = get();
	if (settings.jsonData[category].find(name) == settings.jsonData[category].end())
		return def;
	auto vec = settings.jsonData[category][name];
	return Vec2i(vec[0].get<int>(), vec[1].get<int>());
}

void Settings::save()
{
	Settings& settings = get();

	std::ofstream o("settings.json");
	o << std::setw(4) << settings.jsonData << std::endl;
}

void Settings::load()
{
	if (!filesystem::exists("settings.json"))
		save();

	std::ifstream file("settings.json");

	Settings& settings = get();

	json jsonData;
	file >> jsonData;

	//this combines 2 json objects
	auto diff = json::diff(settings.jsonData, jsonData);
	json newdiff = json::array();
	for (auto& line : diff)
	{
		if (line["op"] != "remove")
			newdiff.push_back(line);
	}
	settings.jsonData = settings.jsonData.patch(newdiff);
}

Settings & Settings::get()
{
	static Settings setings;

	static bool defs(false);
	if (!defs)
	{
		defs = true;
		defaults();
	}

	return setings;
}
