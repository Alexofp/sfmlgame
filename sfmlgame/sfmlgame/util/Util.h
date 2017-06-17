#ifndef UTIL_H
#define UTIL_H

#include "Vec2f.h"
#include <SFML/Graphics/Color.hpp>
#include <string>

struct Line
{
	Vec2f pos;
	Vec2f dir;
};

class Util
{
public:
	Util();
	virtual ~Util();

	static bool boxCollision(Vec2f pos1, Vec2f size1, Vec2f pos2, Vec2f size2);
	static float lineCollision(Line line1, Line line2);
	static void drawLine(Vec2f pos1, Vec2f pos2, sf::Color color = sf::Color::White);
	static float lineDistanceToPoint(Vec2f pos1, Vec2f pos2, Vec2f point);
	static std::wstring strToWStr(std::string str);
	static std::string wStrToStr(std::wstring str);
	static int strToInt(std::string str);
	static int strToInt(std::wstring str);
	static bool fileExists(std::string path);
protected:
private:
};

#endif // UTIL_H
