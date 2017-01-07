#include "Game.h"
#include "Player.h"

Game::Game():State()
{
	auto* player = new Player();
	player->setPos(Vec2f(50, 50));
	entities.push_back(std::unique_ptr<Entity>(player));
}


Game::~Game()
{
}

void Game::update(float dt)
{
	for (auto& entity : entities)
	{
		entity->update(dt);
	}
}

void Game::draw()
{
	for (auto& entity : entities)
	{
		entity->draw();
	}
}
