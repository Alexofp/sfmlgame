#include "GameWindow.h"

GameWindow::GameWindow()
{
	zoomLevel = 1.f;
}


GameWindow::~GameWindow()
{
}

GameWindow& GameWindow::get()
{
	static GameWindow g;
	return g;
}


void GameWindow::open(Vec2i size)
{
	GameWindow& window = get();
	window.window.create(sf::VideoMode(size.x, size.y), "My window");
	window.window.setFramerateLimit(60);
}

void GameWindow::close()
{
	GameWindow& window = get();
	window.window.close();
}

void GameWindow::handleMessages()
{
	GameWindow& gameWindow = get();
	sf::RenderWindow& window = gameWindow.window;

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			if (gameWindow.closeCallback)
			{
				if (gameWindow.closeCallback())
				{
					window.close();
				}
			}
			else
			{
				window.close();
			}
		}
		else
		{
			if (event.type == sf::Event::Resized)
			{
				resizeContent(Vec2i(event.size.width,event.size.height));
			}

			if (gameWindow.eventCallback)
			{
				gameWindow.eventCallback(event);
			}

			
		}
	}
}

void GameWindow::setOnClose(std::function<bool()> func)
{
	GameWindow& window = get();
	window.closeCallback = func;
}

void GameWindow::setOnEvent(std::function<void(sf::Event)> func)
{
	GameWindow& window = get();
	window.eventCallback = func;
}

void GameWindow::clear()
{
	GameWindow& window = get();
	window.window.clear();
}

void GameWindow::display()
{
	GameWindow& window = get();
	window.window.display();
}

bool GameWindow::isOpen()
{
	GameWindow& window = get();

	return window.window.isOpen();
}

Vec2i GameWindow::getMousePos()
{
	GameWindow& window = get();
	
	return Vec2i(sf::Mouse::getPosition(window.window));
}

Vec2i GameWindow::getSize()
{
	GameWindow& window = get();

	return Vec2i(window.getInternalHandle().getSize().x, window.getInternalHandle().getSize().y);
}

sf::RenderWindow & GameWindow::getInternalHandle()
{
	GameWindow& window = get();
	return window.window;
}

bool GameWindow::isFocused()
{
	GameWindow& window = get();
	return window.window.hasFocus();
}

void GameWindow::resizeContent(Vec2i size)
{
	GameWindow& window = get();
	sf::View view = window.getInternalHandle().getView();
	view.setSize(sf::Vector2f(size.getX(), size.getY()));
	view.zoom(window.zoomLevel);
	window.getInternalHandle().setView(view);
}

void GameWindow::setZoom(float z)
{
	GameWindow& window = get();
	window.zoomLevel = z;
	resizeContent(getSize());
}

float GameWindow::getZoom()
{
	GameWindow& window = get();
	return window.zoomLevel;
}

void GameWindow::zoom(float z)
{
	GameWindow& window = get();
	window.zoomLevel = window.zoomLevel*z;
	resizeContent(getSize());
}

void GameWindow::setCameraCenter(Vec2f pos)
{
	GameWindow& window = get();
	sf::View view = window.getInternalHandle().getView();
	view.setCenter(pos.toSFMLVec());
	window.getInternalHandle().setView(view);
}

