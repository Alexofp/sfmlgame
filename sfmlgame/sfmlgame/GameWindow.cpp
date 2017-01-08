#include "GameWindow.h"


GameWindow::GameWindow()
{
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
	}
}

void GameWindow::setOnClose(std::function<bool()> func)
{
	GameWindow& window = get();
	window.closeCallback = func;
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



