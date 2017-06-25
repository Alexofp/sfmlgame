#include "Game.h"
#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Log.h"
#include "DynamicProp.h"
#include "Settings.h"
#include "ObjectManager.h"
#include "GameWindow.h"
#include "HumanAi.h"
#include "Application.h"

Game::Game(std::string ip):State()
{
	world.loadMap("map1");

	Client::connect("127.0.0.1");
	Client::setOnGameInfo([&](sf::Packet& packet) { this->applyGameInfo(packet); });
	Client::setOnPacket([&](Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacket(type, packet); });

	GameWindow::setZoom(2.f);
	sendGameInfoTimer = 0.1f;


	//inventory.addItem({ Vec2i(0,0),Vec2i(0,0) });
	//inventory.addItem({ Vec2i(3,2),Vec2i(1,0) });

	//panel.setInventory(&inventory);
	resizeGui();

}


Game::~Game()
{
}

void Game::update(float dt)
{
	//Server::update(dt);
	Client::update(dt);

	world.localUpdate(dt);
	world.physicsUpdate(dt);

	inventoryScreen.update(dt);

	sendGameInfoTimer -= dt;
	while (sendGameInfoTimer <= 0)
	{
		sendGameInfoTimer += (1.f/30.f);
		Client::send(getClientInfo());
	}
}

void Game::draw()
{
	world.draw();
	if(Settings::getBool("render", "debug", false))
		world.getPhysicsWorld().debugDraw();

	sf::View oldView = GameWindow::getInternalHandle().getView();
	GameWindow::getInternalHandle().setView(guiView);
	drawUI();
	GameWindow::getInternalHandle().setView(oldView);
}

void Game::drawUI()
{
	inventoryScreen.draw();
}

void Game::resizeGui()
{
	Vec2f size = Vec2f(GameWindow::getSize().x, GameWindow::getSize().y);
	guiView.setSize(size.toSFMLVec());
	guiView.setCenter(sf::Vector2f(size.x / 2.f, size.y / 2.f));
	inventoryScreen.resize();
}

void Game::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Resized)
	{
		resizeGui();
	}

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		if (event.mouseWheelScroll.delta > 0)
			GameWindow::zoom(0.9f);
		else
			if (GameWindow::getZoom() < 100.f)
				GameWindow::zoom(1.1f);
	}

	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
	{
		finish();
		Client::disconnect();
		Server::stop();
		app->stopServer();
	}

	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E)
	{
		inventoryScreen.toggle();
	}

	inventoryScreen.handleEvent(event);
}

sf::Packet Game::getClientInfo()
{
	sf::Packet packet;
	if (Client::getClientId() != -1 && players.find(Client::getClientId())!=players.end())
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::MESSAGE;
		players[Client::getClientId()].entity->writeInformation(packet);
	}
	else
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::IGNORE;
	}
	
	return packet;
}

void Game::loadPlayer(Player * player)
{
	inventoryScreen.setPlayer(player);
}

void Game::applyGameInfo(sf::Packet& info)
{
	sf::Uint32 id;
	info >> id;

	Entity* ent = world.findEntity(id);

	if (ent == 0)
	{
		Log::err("[client] Entity with id "+std::to_string(id)+" is not found");
	}
	else if (players.find(Client::getClientId()) != players.end() && id == players[Client::getClientId()].entity->getNid())
	{
		ent->readInformation(info);
	}
	else
	{
		ent->readInformation(info);
	}
}

bool Game::handlePacket(Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::EVENT)
	{
		int from, to;
		std::string eventType;
		packet >> from >> to >> eventType;

		Entity* ent = world.findEntity(to);
		if (ent != 0)
		{
			ent->handleEvent(from, eventType, packet);
		}
	}else if (type == Server::MESSAGE_TYPE::ENTITY_SPAWN)
	{
		sf::Uint8 entTypeB;
		packet >> entTypeB;
		Entity::Type entType = (Entity::Type)entTypeB;
		sf::Uint32 nid;
		packet >> nid;

		Entity* entity = 0;
		if (entType == Entity::Type::Player)
		{
			entity = new Player(nid);
		}
		else if (entType == Entity::Type::DynamicProp)
		{
			entity = new DynamicProp(nid);
		}
		else if (entType == Entity::Type::HumanAi)
		{
			entity = new HumanAi(nid);
		}
		if (entity != 0)
		{
			world.add(entity);
			entity->readSpawn(packet);

			if (entType == Entity::Type::Player)
			{
				ClientPlayerInfo playerinfo;
				playerinfo.entity = (Player*)entity;

				players[((Player*)entity)->getClientId()] = playerinfo;

				Log::debug("Player with id " + std::to_string(entity->getNid()));

				if (((Player*)entity)->getClientId() != Client::getClientId())
				{
					((Player*)entity)->setRemote(true);
				}
				else
				{
					loadPlayer((Player*)entity);
				}
			}
			
		}

	}
	else
	{
		Log::err("[client] WTF "+std::to_string((int)type));
	}

	return false;
}


