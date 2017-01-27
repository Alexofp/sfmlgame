#include "Button.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"

Button::Button() :Widget()
{
	//ctor
	shouldUpdate = true;
	box.setFillColor(sf::Color::Blue);

	text.setString("Button");
	setTextSize(16);
	text.setFont(Gui::getDefaultFont());
	im.setTextureRect(Vec2f(10.f, 10.f));
	//im.setMult(10.f);
	mult = 0.4f;
}

Button::~Button()
{
	//dtor
}

void Button::draw()
{
	if (shouldUpdate)
	{
		redraw();
		shouldUpdate = false;
	}
	//Window::getWindow().draw( box );
	im.draw();
	GameWindow::getInternalHandle().draw(text);
}

void Button::handleEvent(WidgetEvent& event)
{
	if (!event.handled)
	{
		//std::cout << "Event" << std::endl;
		if (event.type == WidgetEventType::MouseDown)
		{
			if (Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), getPos(), getSize()))
			{
				event.handled = true;
				if (onClick)
				{
					onClick(this, event.mouseDown);
				}
			}
		}
	}
}

void Button::setColor(sf::Color color)
{
	box.setFillColor(color);
}

void Button::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
	shouldUpdate = true;
}

void Button::setMult(float m)
{
	mult = m;
	im.setMult(m);
}

void Button::redraw()
{
	im.setPos(getPos());
	im.setSize(getSize());
	im.setMult(mult);

	box.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	box.setSize(sf::Vector2f(getSize().getX(), getSize().getY()));
	box.setOrigin(sf::Vector2f(getSize().getX(), getSize().getY()) / 2.f);


	sf::FloatRect boundingBox = text.getLocalBounds();

	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	text.setOrigin(boundingBox.width / 2, lineSpacing / 2);
}

void Button::OnClick(std::function<void(Button*, MouseDownEvent)> func)
{
	onClick = func;
}

void Button::init(GuiHandler* handler)
{
}

void Button::setTexture(std::string texture)
{
	im.setTexture(texture);
}

void Button::setText(std::wstring str)
{
	text.setString(str);
	sf::FloatRect boundingBox = text.getLocalBounds();

	float lineSpacing = Gui::getDefaultFont().getLineSpacing(text.getCharacterSize());

	text.setPosition(sf::Vector2f(getPos().getX(), getPos().getY()));
	text.setOrigin(boundingBox.width / 2, lineSpacing / 2);
}