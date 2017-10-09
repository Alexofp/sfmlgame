#include "Util.h"
#include <SFML/Graphics/Vertex.hpp>
#include "GameWindow.h"
#include <filesystem>

Util::Util()
{
	//ctor
}

Util::~Util()
{
	//dtor
}

bool Util::boxCollision(Vec2f pos1, Vec2f size1, Vec2f pos2, Vec2f size2)
{
	if ((pos1.getX() + size1.getX() / 2 > pos2.getX() - size2.getX() / 2) &&
		(pos1.getX() - size1.getX() / 2 < pos2.getX() + size2.getX() / 2) &&
		(pos1.getY() + size1.getY() / 2 > pos2.getY() - size2.getY() / 2) &&
		(pos1.getY() - size1.getY() / 2 < pos2.getY() + size2.getY() / 2)
		)
		return true;
	return false;
}

bool Util::boxCollision2(Vec2f pos1, Vec2f size1, Vec2f pos2, Vec2f size2)
{
	if ((pos1.getX() + size1.getX() > pos2.getX() ) &&
		(pos1.getX() < pos2.getX() + size2.getX() ) &&
		(pos1.getY() + size1.getY() > pos2.getY() ) &&
		(pos1.getY() < pos2.getY() + size2.getY() )
		)
		return true;
	return false;
}

float Util::lineCollision(Line line1, Line line2)
{
	float r_px = line1.pos.getX();
	float r_py = line1.pos.getY();

	float r_dx = line1.dir.getX();
	float r_dy = line1.dir.getY();


	float s_px = line2.pos.getX();
	float s_py = line2.pos.getY();

	float s_dx = line2.dir.getX();
	float s_dy = line2.dir.getY();

	float T2 = (r_dx*(s_py - r_py) + r_dy*(r_px - s_px)) / (s_dx*r_dy - s_dy*r_dx);
	if (T2 < 0 || T2>1)
	{
		return -1.f;
	}
	float T1 = (s_px + s_dx*T2 - r_px) / r_dx;
	return T1;
}

void Util::drawLine(Vec2f pos1, Vec2f pos2, sf::Color color)
{
	sf::Vertex vertices[2] =
	{
		sf::Vertex(pos1.toSFMLVec(), color),
		sf::Vertex(pos2.toSFMLVec(), color)
	};
	GameWindow::getInternalHandle().draw(vertices, 2, sf::Lines);
}

float Util::lineDistanceToPoint(Vec2f pos1, Vec2f pos2, Vec2f point)
{
	Vec2f pos2d = Vec2f::sub(pos2, pos1);
	Vec2f pointd = Vec2f::sub(point, pos1);

	float dist = Vec2f::distanceSquared(pos1, pos2);
	if (dist == 0.f)
		return Vec2f::distance(pos1, point);

	float t = std::max(0.f, std::min(1.f, Vec2f::dot(pointd,pos2d)/dist));
	Vec2f projection = Vec2f::add(pos1, Vec2f::mul(pos2d,t));

	return Vec2f::distance(point, projection);
}

std::wstring Util::strToWStr(std::string str)
{
	return std::wstring(str.begin(), str.end());
}

std::string Util::wStrToStr(std::wstring str)
{
	return std::string(str.begin(), str.end());
}

int Util::strToInt(std::string str)
{
	try
	{
		int n = std::stoi(str);
		return n;
	}
	catch (std::invalid_argument e)
	{
		return 0;
	}
}

int Util::strToInt(std::wstring str)
{
	return strToInt(wStrToStr(str));
}

bool Util::fileExists(std::string path)
{
	return std::experimental::filesystem::exists(path);;
}

Vec2f Util::fitView(Vec2f screenSize, Vec2f panelSize, float margin)
{
	panelSize.x += margin;
	panelSize.y += margin;
	float aspect = screenSize.x / screenSize.y;

	float aspect2 = panelSize.x / panelSize.y;

	Vec2f newsize;
	if (aspect > aspect2)
	{
		newsize = Vec2f(panelSize.y*aspect, panelSize.y);
	}
	else
	{
		newsize = Vec2f(panelSize.x, panelSize.x/aspect);
	}
	

	return newsize;
}

float Util::angleDifference(float ang1, float ang2)
{
	float targetAngle = ang1;
	while (targetAngle > 180.f)
		targetAngle -= 360.f;
	while (targetAngle < -180.f)
		targetAngle += 360.f;
	float currentAngle = ang2;
	while (currentAngle > 180.f)
		currentAngle -= 360.f;
	while (currentAngle < -180.f)
		currentAngle += 360.f;
	float delta = targetAngle - currentAngle;
	if (delta > 180)
	{
		targetAngle -= 360.f;
	}
	if (delta < -180)
	{
		targetAngle += 360.f;
	}

	return (targetAngle - currentAngle);
}
