#include "GuiHandler.h"
#include "GameWindow.h"

GuiHandler::GuiHandler()
{
	//ctor
	guiView = GameWindow::getInternalHandle().getDefaultView();
}

GuiHandler::~GuiHandler()
{
	//dtor
}

void GuiHandler::draw()
{
	sf::View old = GameWindow::getInternalHandle().getView();

	GameWindow::getInternalHandle().setView(guiView);
	for (auto& widget : childs)
	{
		if (widget->isVisible())
			widget->draw();
	}
	GameWindow::getInternalHandle().setView(old);
}

void GuiHandler::handleEvent(WidgetEvent& event)
{
	if (event.type == WidgetEventType::Resized)
	{
		guiView.setCenter(Vec2f::mul(event.resized.size, 0.5f).toSFMLVec());
		guiView.setSize(event.resized.size.toSFMLVec());
	}

	for (std::vector<std::unique_ptr<Widget> >::reverse_iterator it = childs.rbegin(); it != childs.rend(); it++)
	{
		if (event.type == WidgetEventType::MouseDown)
		{
			event.mouseDown.pos = GameWindow::getInternalHandle().mapPixelToCoords(event.originalMousePos.toSFMLVec(), getView());
		}
		if (event.type == WidgetEventType::MouseUp)
		{
			event.mouseUp.pos = GameWindow::getInternalHandle().mapPixelToCoords(event.originalMousePos.toSFMLVec(), getView());
		}
		if (event.type == WidgetEventType::MouseMove)
		{
			event.mouseMove.pos = GameWindow::getInternalHandle().mapPixelToCoords(event.originalMousePos.toSFMLVec(), getView());
		}

		if ((*it)->isVisible() || event.type == WidgetEventType::Resized)
			(*it)->handleEvent(event);
	}
}

void GuiHandler::add(Widget* widget, std::string id)
{
	widget->setId(id);
	widget->setHandler(this);
	widget->init(this);
	childs.push_back(std::unique_ptr<Widget>(widget));
}

Widget* GuiHandler::findById(std::string id)
{
	for (auto& w : childs)
	{
		if (w->getId() == id)
			return w.get();
	}
	return 0;
}

void GuiHandler::redraw()
{

}

sf::View GuiHandler::getView()
{
	return guiView;
}

void GuiHandler::setView(sf::View view)
{
	guiView = view;
}

void GuiHandler::init(GuiHandler* handler)
{

}