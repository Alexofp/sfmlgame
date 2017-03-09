#include "Panel.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"
#include "TextureManager.h"

Panel::Panel() :Widget()
{
	//ctor
	isDraging = false;
}

Panel::~Panel()
{
	//dtor
}

void Panel::draw()
{
	//Window::getWindow().draw(box);
	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}
	im.draw();
}

void Panel::handleEvent(WidgetEvent& event)
{
	if (!event.handled && event.type == WidgetEventType::MouseDown)
	{
		if (Util::boxCollision(event.mouseDown.pos, Vec2f(1.f, 1.f), getPos(), getSize()))
		{
			event.handled = true;
			isDraging = true;
			storedPos = event.mouseDown.pos;
		}
	}
	if (event.type == WidgetEventType::MouseUp)
	{
		if (!event.handled && Util::boxCollision(event.mouseUp.pos, Vec2f(1.f, 1.f), getPos(), getSize()))
		{
			event.handled = true;
		}
		isDraging = false;
	}
	if (event.type == WidgetEventType::MouseMove)
	{
		if (isDraging)
		{
			Vec2f delta = Vec2f::sub(event.mouseMove.pos, storedPos);
			event.handled = true;

			if (onDrag)
			{
				onDrag(this, event.mouseMove, delta);
			}
		}
	}
}

void Panel::redraw()
{
	im.setPos(getPos());
	im.setSize(getSize());
	im.setTextureRect(Vec2f(10.f, 10.f));

	box.setPosition(getPos().toSFMLVec());
	box.setSize(getSize().toSFMLVec());
	box.setOrigin(getSize().toSFMLVec() / 2.f);
}

void Panel::setTexture(std::string texture)
{
	box.setTexture(TextureManager::get(texture));
	im.setTexture(texture);
}

void Panel::init(GuiHandler* handler)
{

}

void Panel::setColor(sf::Color color)
{
	box.setFillColor(color);
	im.setColor(color);
}

void Panel::OnDrag(std::function<void(Panel*, MouseMoveEvent, Vec2f)> f)
{
	onDrag = f;
}