#include "Application.h"
#include "GameWindow.h"
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "Input.h"
#include "TextureManager.h"

Application::Application()
{
}


Application::~Application()
{
}

void Application::pushState(State * state)
{
	states.push_back(std::unique_ptr<State>(state));
	state->app = this;
}

int Application::run()
{
	GameWindow::open(Vec2i(200, 200));
	GameWindow::setOnClose([&]() { return true; });
	TextureManager::load("player", "resources/player.png");

	sf::Clock clock;

	pushState(new Game());

	while (states.size()>0 && GameWindow::isOpen())
	{
		sf::Time elapsed = clock.restart();

		GameWindow::handleMessages();

		Input::update();
		states.back()->update(elapsed.asSeconds());

		GameWindow::clear();
		states.back()->draw();
		GameWindow::display();
	}

	return 0;
}