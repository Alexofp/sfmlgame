#include "Gui.h"
#include "Widget.h"
#include "GameWindow.h"

Gui::Gui()
{
	//ctor
	triggerResize();
}

Gui::~Gui()
{
	//dtor
}

void Gui::draw()
{
	//handler.setPos( Vec2f::sum(handler.getView().getCenter(),Vec2f::mul(handler.getView().getSize(),0.5f)));
	handler.draw();
}

sf::View Gui::getView()
{
	return handler.getView();
}

void Gui::triggerResize()
{
	WidgetEvent e;
	e.handled = false;
	e.type = WidgetEventType::Resized;
	e.resized.size = Vec2f(GameWindow::getSize().x, GameWindow::getSize().y);
	handler.handleEvent(e);
}

bool Gui::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		WidgetEvent e;
		e.handled = false;
		e.type = WidgetEventType::MouseDown;
		e.mouseDown.button = event.mouseButton.button;

		sf::Vector2i windowPos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f newPos = GameWindow::getInternalHandle().mapPixelToCoords(windowPos, handler.getView());
		e.originalMousePos = Vec2i(event.mouseButton.x, event.mouseButton.y);

		e.mouseDown.pos = Vec2f(newPos);
		handler.handleEvent(e);
		return e.handled;
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		WidgetEvent e;
		e.handled = false;
		e.type = WidgetEventType::MouseUp;
		e.mouseUp.button = event.mouseButton.button;

		sf::Vector2i windowPos(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2f newPos = GameWindow::getInternalHandle().mapPixelToCoords(windowPos, handler.getView());
		e.originalMousePos = Vec2i(event.mouseButton.x, event.mouseButton.y);

		e.mouseUp.pos = Vec2f(newPos);
		handler.handleEvent(e);
		return e.handled;
	}
	if (event.type == sf::Event::MouseMoved)
	{
		WidgetEvent e;
		e.handled = false;
		e.type = WidgetEventType::MouseMove;
		e.mouseMove.pos = Vec2f(event.mouseMove.x, event.mouseMove.y);
		e.originalMousePos = Vec2i(event.mouseMove.x, event.mouseMove.y);
		handler.handleEvent(e);
		return e.handled;
	}
	if (event.type == sf::Event::Resized)
	{
		WidgetEvent e;
		e.handled = false;
		e.type = WidgetEventType::Resized;
		e.resized.size = Vec2f(event.size.width, event.size.height);
		handler.handleEvent(e);
		return e.handled;
	}
	if (event.type == sf::Event::TextEntered)
	{
		WidgetEvent e;
		e.handled = false;
		e.type = WidgetEventType::TextEntered;
		e.textEntered.key = event.text.unicode;
		handler.handleEvent(e);
		return e.handled;
	}
	return false;
}

void Gui::add(Widget* widget, std::string id)
{
	handler.add(widget, id);
}

Widget* Gui::findById(std::string id)
{
	return handler.findById(id);
}

sf::Font& Gui::getDefaultFont()
{
	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
	{
		font.loadFromFile("resources/DejaVuSans.ttf");
	}
	loaded = true;
	return font;
}
