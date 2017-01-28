#include "Widget.h"
#include "GameWindow.h"
#include "GuiHandler.h"

Widget::Widget()
{
	//ctor
	shouldUpdate = false;
	visible = true;
	shouldDestroy = false;
}

Widget::~Widget()
{
	//dtor
}

void Widget::setPos(Vec2f p)
{
	pos = p;
	shouldUpdate = true;
}

void Widget::setSize(Vec2f s)
{
	size = s;
	shouldUpdate = true;
}

Vec2f Widget::getPos()
{
	return pos;
}

Vec2f Widget::getSize()
{
	return size;
}

void Widget::setHandler(GuiHandler* h)
{
	handler = h;
}

Vec2i Widget::getRealPos()
{
	return Vec2i(GameWindow::getInternalHandle().mapCoordsToPixel(getPos().toSFMLVec(), handler->getView()));
}

void Widget::destroy()
{
	shouldDestroy = true;
}

bool Widget::isDestroyed()
{
	return shouldDestroy;
}

void Widget::show()
{
	visible = true;
	onVisibityChange();
}

void Widget::hide()
{
	visible = false;
	onVisibityChange();
}

bool Widget::isVisible()
{
	return visible;
}

void Widget::setId(std::string i)
{
	id = i;
}

std::string Widget::getId()
{
	return id;
}

void Widget::onVisibityChange()
{

}