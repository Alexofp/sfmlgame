#include "Application.h"
#include "GameWindow.h"
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "Input.h"
#include "TextureManager.h"
#include "GameServer.h"
#include <iostream>
#include "AnimationEditor.h"

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
	TextureManager::loadFromFile("resources/gui/textures.txt");
	TextureManager::loadFromFile("resources/somedude/textures.txt");
	TextureManager::load("player", "resources/player.png");
	TextureManager::load("blueprint", "resources/blueprint.png");

	GameWindow::open(Vec2i(800, 700));
	GameWindow::setOnClose([&]() { return true; });
	GameWindow::setOnEvent([&](sf::Event e) { states.back()->handleEvent(e); });
	

	sf::Clock clock;

	bool isServer;
	//std::cout << "Server?" << std::endl;
	//std::cin >> isServer;
	isServer = false;

	std::unique_ptr<GameServer> server(nullptr);
	if (isServer)
		server.reset(new GameServer());

	//pushState(new Game());
	pushState(new AnimationEditor());

	while (states.size()>0 && GameWindow::isOpen())
	{
		sf::Time elapsed = clock.restart();
		GameWindow::handleMessages();

		states.back()->update(elapsed.asSeconds());
		if(isServer)
			server->update(elapsed.asSeconds());

		Input::update();

		GameWindow::clear();
		states.back()->draw();
		GameWindow::display();
	}

	return 0;
}