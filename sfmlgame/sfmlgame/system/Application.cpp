#include "Application.h"
#include "GameWindow.h"
#include <SFML/System/Clock.hpp>
#include "Game.h"
#include "Input.h"
#include "TextureManager.h"
#include <iostream>
#include "AnimationEditor.h"
#include "Settings.h"
#include "GameMenu.h"
#include "MapEditor.h"
#include "ObjectManager.h"
#include "AnimationManager.h"

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
	Settings::load();
	Settings::save();

	TextureManager::loadFromFile("resources/ground/textures.txt");
	TextureManager::loadFromFile("resources/props/textures.txt");
	TextureManager::loadFromFile("resources/gui/textures.txt");
	TextureManager::loadFromFile("resources/somedude/textures.txt");
	TextureManager::loadFromFile("resources/player/player.txt");
	TextureManager::load("player", "resources/player.png");
	TextureManager::load("blueprint", "resources/blueprint.png");
	ObjectManager::loadFromFile("objects.txt");

	AnimationManager::loadAnimation("person_idle","resources/player/walkanim.json");
	AnimationManager::loadAnimation("person_hit","resources/player/hitanim.json");
	AnimationManager::getAnimation("person_hit")->setLooped(false);
	AnimationManager::loadAnimation("person_walk", "resources/player/walk123.json");

	GameWindow::open(Settings::getVec2i("window","size",Vec2i(800,600)), Settings::getBool("window","fullscreen", false));
	GameWindow::setOnClose([&]() { return true; });
	GameWindow::setOnEvent([&](sf::Event e) { states.back()->handleEvent(e); });
	

	sf::Clock clock;
	isServer = false;
	pushState(new GameMenu());

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

		if (states.back()->finished)
			states.pop_back();
	}

	return 0;
}

void Application::startServer()
{
	isServer = true;
	server.reset(new GameServer());
}
