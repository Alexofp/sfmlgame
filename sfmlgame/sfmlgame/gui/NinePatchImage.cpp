#include "NinePatchImage.h"
#include "GameWindow.h"
#include "TextureManager.h"

NinePatchImage::NinePatchImage()
{
	//ctor
	mult = 1.f;
	shouldUpdate = true;
	color = sf::Color::White;
}

NinePatchImage::~NinePatchImage()
{
	//dtor
}

void NinePatchImage::redraw()
{
	shapes.clear();

	sf::RectangleShape lt;
	lt.setOrigin(0.f, 0.f);
	lt.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, 0.f) - getSize().toSFMLVec() / 2.f);
	lt.setSize(textureRect.toSFMLVec()*mult);
	//lt.setFillColor(sf::Color::Red);
	if (texture != "")
	{
		lt.setTexture(TextureManager::get(texture));
		lt.setTextureRect(sf::IntRect(0, 0, textureRect.getX(), textureRect.getY()));
	}

	shapes.push_back(lt);

	sf::RectangleShape rt;
	rt.setOrigin(textureRect.getX()*mult, 0.f);
	rt.setPosition(getPos().toSFMLVec() + sf::Vector2f(getSize().getX(), 0.f) - getSize().toSFMLVec() / 2.f);
	rt.setSize(textureRect.toSFMLVec()*mult);
	//rt.setFillColor(sf::Color::Red);
	if (texture != "")
	{
		rt.setTexture(TextureManager::get(texture));
		rt.setTextureRect(sf::IntRect(TextureManager::get(texture)->getSize().x - textureRect.getX(), 0, textureRect.getX(), textureRect.getY()));
	}
	shapes.push_back(rt);

	sf::RectangleShape ld;
	ld.setOrigin(0.f, textureRect.getY()*mult);
	ld.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, getSize().getY()) - getSize().toSFMLVec() / 2.f);
	ld.setSize(textureRect.toSFMLVec()*mult);
	//ld.setFillColor(sf::Color::Red);
	if (texture != "")
	{
		ld.setTexture(TextureManager::get(texture));
		ld.setTextureRect(sf::IntRect(0, TextureManager::get(texture)->getSize().y - textureRect.getY(), textureRect.getX(), textureRect.getY()));
	}
	shapes.push_back(ld);

	sf::RectangleShape rd;
	rd.setOrigin(textureRect.getX()*mult, textureRect.getY()*mult);
	rd.setPosition(getPos().toSFMLVec() + sf::Vector2f(getSize().getX(), getSize().getY()) - getSize().toSFMLVec() / 2.f);
	rd.setSize(textureRect.toSFMLVec()*mult);
	//rd.setFillColor(sf::Color::Red);
	if (texture != "")
	{
		rd.setTexture(TextureManager::get(texture));
		rd.setTextureRect(sf::IntRect(TextureManager::get(texture)->getSize().x - textureRect.getX(), TextureManager::get(texture)->getSize().y - textureRect.getY(), textureRect.getX(), textureRect.getY()));
	}
	shapes.push_back(rd);


	sf::RectangleShape tline;
	tline.setOrigin(-textureRect.getX()*mult, 0);
	tline.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, 0.f) - getSize().toSFMLVec() / 2.f);
	tline.setSize(Vec2f(getSize().getX() - 2 * textureRect.getX()*mult, textureRect.getY()*mult).toSFMLVec());
	//tline.setFillColor(sf::Color::Blue);
	if (texture != "")
	{
		tline.setTexture(TextureManager::get(texture));
		tline.setTextureRect(sf::IntRect(textureRect.getX(), 0, TextureManager::get(texture)->getSize().x - 2 * textureRect.getX(), textureRect.getY()));
	}
	shapes.push_back(tline);

	sf::RectangleShape dline;
	dline.setOrigin(-textureRect.getX()*mult, textureRect.getY()*mult);
	dline.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, getSize().getY()) - getSize().toSFMLVec() / 2.f);
	dline.setSize(Vec2f(getSize().getX() - 2 * textureRect.getX()*mult, textureRect.getY()*mult).toSFMLVec());
	//dline.setFillColor(sf::Color::Green);
	if (texture != "")
	{
		dline.setTexture(TextureManager::get(texture));
		dline.setTextureRect(sf::IntRect(textureRect.getX(), TextureManager::get(texture)->getSize().y - textureRect.getY(), TextureManager::get(texture)->getSize().x - 2 * textureRect.getX(), textureRect.getY()));
	}
	shapes.push_back(dline);


	sf::RectangleShape lline;
	lline.setOrigin(0.f, -textureRect.getY()*mult);
	lline.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, 0.f) - getSize().toSFMLVec() / 2.f);
	lline.setSize(Vec2f(textureRect.getX()*mult, getSize().getY() - textureRect.getY()*mult*2.f).toSFMLVec());
	//lline.setFillColor(sf::Color::Yellow);
	if (texture != "")
	{
		lline.setTexture(TextureManager::get(texture));
		lline.setTextureRect(sf::IntRect(0, textureRect.getY(), textureRect.getX(), TextureManager::get(texture)->getSize().y - 2 * textureRect.getY()));
	}
	shapes.push_back(lline);

	sf::RectangleShape rline;
	rline.setOrigin(textureRect.getX()*mult, -textureRect.getY()*mult);
	rline.setPosition(getPos().toSFMLVec() + sf::Vector2f(getSize().getX(), 0.f) - getSize().toSFMLVec() / 2.f);
	rline.setSize(Vec2f(textureRect.getX()*mult, getSize().getY() - textureRect.getY()*mult*2.f).toSFMLVec());
	//rline.setFillColor(sf::Color::Yellow);
	if (texture != "")
	{
		rline.setTexture(TextureManager::get(texture));
		rline.setTextureRect(sf::IntRect(TextureManager::get(texture)->getSize().x - textureRect.getX(), textureRect.getY(), textureRect.getX(), TextureManager::get(texture)->getSize().y - 2 * textureRect.getY()));
	}
	shapes.push_back(rline);

	sf::RectangleShape center;
	center.setOrigin(-textureRect.getX()*mult, -textureRect.getY()*mult);
	center.setPosition(getPos().toSFMLVec() + sf::Vector2f(0.f, 0.f) - getSize().toSFMLVec() / 2.f);
	center.setSize(Vec2f(getSize().getX() - textureRect.getX()*mult*2.f, getSize().getY() - textureRect.getY()*mult*2.f).toSFMLVec());
	//center.setFillColor(sf::Color::Magenta);
	if (texture != "")
	{
		center.setTexture(TextureManager::get(texture));
		center.setTextureRect(sf::IntRect(textureRect.getX(), textureRect.getY(), TextureManager::get(texture)->getSize().x - 2 * textureRect.getX(), TextureManager::get(texture)->getSize().y - 2 * textureRect.getY()));
	}
	shapes.push_back(center);

	for (auto& shape : shapes)
	{
		shape.setFillColor(color);
	}
}

void NinePatchImage::setPos(Vec2f p)
{
	pos = p;
	shouldUpdate = true;
}

void NinePatchImage::setSize(Vec2f s)
{
	size = s;
	shouldUpdate = true;
}

Vec2f NinePatchImage::getPos()
{
	return pos;
}

Vec2f NinePatchImage::getSize()
{
	return size;
}

void NinePatchImage::setTexture(std::string t)
{
	texture = t;
	shouldUpdate = true;
}

void NinePatchImage::setTextureRect(Vec2f t)
{
	textureRect = t;
	shouldUpdate = true;
}

void NinePatchImage::setMult(float m)
{
	mult = m / textureRect.getY()*getSize().getY();
	shouldUpdate = true;
}

void NinePatchImage::setColor(sf::Color color)
{
	this->color = color;

	for (auto& shape : shapes)
	{
		shape.setFillColor(color);
	}
}

void NinePatchImage::draw()
{
	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}

	for (auto& shape : shapes)
	{
		GameWindow::getInternalHandle().draw(shape);
	}
}