#include "EditBox.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"
#include <SFML/System/Clock.hpp>

EditBox::EditBox() :Widget()
{
	//ctor
	isFocused = false;
	text.setFont(Gui::getDefaultFont());
	im.setTextureRect(Vec2f(10.f, 10.f));
}

EditBox::~EditBox()
{
	//dtor
}

void EditBox::draw()
{
	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}
	//Window::getWindow().draw( box );
	im.draw();

	if (isFocused)
	{
		static sf::Clock clock;
		if (((int)(clock.getElapsedTime().asSeconds()*1.3f)) % 2 == 0)
		{
			text.setString(str + L"|");
		}
		else
		{
			text.setString(str);
		}
		if (clock.getElapsedTime().asSeconds() > 1.3f)
			clock.restart();
	}
	else
	{
		text.setString(str);
	}

	GameWindow::getInternalHandle().draw(text);
}

void EditBox::handleEvent(WidgetEvent& event)
{
	if (true)
	{
		//std::cout << "Event" << std::endl;
		if (event.type == WidgetEventType::MouseDown)
		{
			isFocused = false;

			if (!event.handled && Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), getPos(), getSize()))
			{
				event.handled = true;
				isFocused = true;
			}
		}
		if (event.type == WidgetEventType::TextEntered)
		{
			if (!event.handled && isFocused)
			{
				wchar_t c = (wchar_t)event.textEntered.key;
				if ((iswalpha(c) || iswalnum(c) || iswgraph(c) || iswspace(c))
					&& event.textEntered.key != 13)
				{
					str = str + c;
				}
				if (event.textEntered.key == 8 && str.size() > 0)
				{
					str.pop_back();
				}
				if (event.textEntered.key == 13)
				{

				}

				sf::FloatRect boundingBox = text.getLocalBounds();

				float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

				text.setPosition(sf::Vector2f(getPos().getX() - getSize().getX() / 2.f, getPos().getY()));
				text.setOrigin(-2.f, lineSpacing / 2);
			}
		}
	}

}

void EditBox::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
	shouldUpdate = true;
}

void EditBox::redraw()
{
	im.setPos(getPos());
	im.setSize(getSize());

	sf::FloatRect boundingBox = text.getLocalBounds();

	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX() - getSize().getX() / 2.f, getPos().getY()));
	text.setOrigin(-2.f, lineSpacing / 2);
}

void EditBox::init(GuiHandler* handler)
{
}

void EditBox::setTexture(std::string texture)
{
	im.setTexture(texture);
}

void EditBox::setText(std::wstring s)
{
	str = s;
	text.setString(str);
	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX() - getSize().getX() / 2.f, getPos().getY()));
	text.setOrigin(-2.f, lineSpacing / 2);
}

std::wstring EditBox::getText()
{
	return str;
}