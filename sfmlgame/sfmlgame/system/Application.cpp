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
#include "ItemManager.h"
#include "WeaponManager.h"

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
	TextureManager::loadFromFile("resources/items/textures.txt");
	TextureManager::loadFromFile("resources/somedude/textures.txt");
	TextureManager::loadFromFile("resources/player/player.txt");
	TextureManager::load("player", "resources/player.png");
	TextureManager::load("blueprint", "resources/blueprint.png");
	ObjectManager::loadFromFile("objects.txt");
	WeaponManager::loadFromFile("weapons.txt");

	AnimationManager::loadAnimation("person_idle","resources/player/walkanim.json");
	AnimationManager::loadAnimation("person_hit","resources/player/hitanim.json");
	AnimationManager::getAnimation("person_hit")->setLooped(false);
	AnimationManager::loadAnimation("person_walk", "resources/player/walk123.json");

	AnimationManager::loadAnimation("ak74_idle", "resources/weapon_idle.json");
	AnimationManager::loadAnimation("ak74_walk", "resources/weapon_walk.json");
	AnimationManager::loadAnimation("ak74_attack", "resources/weapon_attack.json");
	AnimationManager::getAnimation("ak74_attack")->setLooped(false);

	AnimationManager::loadAnimation("legs_idle", "resources/player/legs_idle.json");
	AnimationManager::loadAnimation("legs_walk", "resources/player/legs_walk.json");

	ItemManager::loadItems("items.txt");

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

		if (isServer)
			server->draw();
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

void Application::stopServer()
{
	isServer = false;
	server.reset(0);
}