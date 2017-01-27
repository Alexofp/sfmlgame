#include "GuiWindow.h"
#include "Panel.h"
#include "Util.h"
#include <iostream>
#include "GameWindow.h"
#include "Gui.h"
#include "TextureManager.h"

GuiWindow::GuiWindow() :Widget()
{
	//ctor
	titlebar = 30.f;
}

GuiWindow::~GuiWindow()
{
	//dtor
}

void GuiWindow::init(GuiHandler* handler)
{


	panel = new Panel();
	panel->setPos(getSize().toSFMLVec() / 2.f);
	panel->setSize(getSize().toSFMLVec());
	panel->setTexture("window");
	gui.add(panel);

	panel2 = new Panel();
	panel2->setPos(getSize().toSFMLVec() / 2.f - sf::Vector2f(0.f, titlebar / 2.f + getSize().getY() / 2.f));
	panel2->setSize(Vec2f(getSize().getX(), titlebar).toSFMLVec());
	panel2->setColor(sf::Color(100, 100, 100));
	panel2->setTexture("titlebar");
	panel2->OnDrag(std::bind(&GuiWindow::onDrag, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	gui.add(panel2);

	shouldUpdate = true;

}

void GuiWindow::draw()
{
	/*f::RectangleShape s;
	s.setPosition(getPos().toSFMLVec());
	s.setSize(getSize().toSFMLVec());
	s.setOrigin(getSize().toSFMLVec()/2.f);
	Window::getWindow().draw(s);*/

	if (shouldUpdate)
	{
		shouldUpdate = false;
		redraw();
	}

	gui.draw();
}

void GuiWindow::handleEvent(WidgetEvent& event)
{
	gui.handleEvent(event);

	if (event.type == WidgetEventType::Resized)
	{
		shouldUpdate = true;
	}

}

void GuiWindow::redraw()
{
	if (!ignoreS)
	{
		panel->setPos(getSize().toSFMLVec() / 2.f);
		panel->setSize(getSize().toSFMLVec());
		panel2->setPos(getSize().toSFMLVec() / 2.f - sf::Vector2f(0.f, titlebar / 2.f + getSize().getY() / 2.f));
		panel2->setSize(Vec2f(getSize().getX(), titlebar).toSFMLVec());
	}

	gui.setPos(Vec2f::sub((getPos()), Vec2f::mul(getSize(), -0.5)));
	sf::View view = gui.getView();

	//view.move()
	view.setCenter(sf::Vector2f(GameWindow::getInternalHandle().getSize())*0.5f + -1.f*getPos().toSFMLVec() + getSize().toSFMLVec() / 2.f);
	//guiView.setCenter( getPos().toSFMLVec()+ Vec2f::mul(event.resized.size,0.5f).toSFMLVec() );
	//view.setSize(Window::getWindow().getSize().x,Window::getWindow().getSize().y);

	//view.setCenter( getPos().getX()+getSize().getX()/2.f,getPos().getY()+Window::getWindow().getSize().y/2.f );
	gui.setView(view);
}

void GuiWindow::onDrag(Panel* sender, MouseMoveEvent e, Vec2f delta)
{
	ignoreS = true;
	setPos(Vec2f::add(getPos(), delta));
	ignoreS = false;
}

void GuiWindow::add(Widget* widget, std::string id)
{
	gui.add(widget, id);
}

Widget* GuiWindow::findById(std::string id)
{
	return gui.findById(id);
}