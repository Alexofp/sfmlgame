#include "Game.h"
#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Log.h"
#include "DynamicProp.h"

Game::Game(std::string ip):State()
{
	terrain.load("maps/map1/");

	Client::connect("127.0.0.1");
	Client::setOnGameInfo([&](sf::Packet& packet) { this->applyGameInfo(packet); });
	Client::setOnPacket([&](Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacket(type, packet); });
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
}

void Game::draw()
{
	terrain.draw();
	world.draw();
	world.getPhysicsWorld().debugDraw();
}

void Game::handleEvent(sf::Event event)
{
}

sf::Packet Game::getClientInfo()
{
	sf::Packet packet;
	if (Client::getClientId() != -1 && players.find(Client::getClientId())!=players.end())
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::MESSAGE;
		auto message = players[Client::getClientId()].entity->writeInformation();
		message.write(packet);
	}
	else
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::IGNORE;
	}
	
	return packet;
}

void Game::applyGameInfo(sf::Packet& info)
{
	int count;
	sf::Uint16 c;
	info >> c;
	count = c;

	for (int i = 0; i < count; i++)
	{
		sf::Uint32 id;
		info >> id;

		sf::Uint8 entityType;
		info >> entityType;

		MultiplayerMessage message(info);

		Entity* ent = world.findEntity(id);

		if (ent == 0)
		{
			Log::err("Something is very wrong "+std::to_string(count));
		}
		else if (id == players[Client::getClientId()].entity->getNid())
		{
		}else
		{
			//Log::debug("its ok");
			ent->readInformation(message);
		}
	}

	Client::send(getClientInfo());
}

bool Game::handlePacket(Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::MESSAGE)
	{
		MultiplayerMessage message(packet);

		if (message.getType() == MessageType::SpawnPlayerEntity)
		{
			auto* m = message.getMessage<SpawnPlayerEntityMessage>();

			Player* player = new Player(m->playerId, m->nid);
			player->setPos(Vec2f(m->x, m->y));
			ClientPlayerInfo playerinfo;
			playerinfo.entity = player;

			players[m->playerId] = playerinfo;

			Log::debug("Player with id " + std::to_string(m->nid));

			if (m->playerId != Client::getClientId())
			{
				player->setRemote(true);
			}
			world.add(player);
		}
		if (message.getType() == MessageType::SpawnDynamicPropEntity)
		{
			auto* m = message.getMessage<SpawnDynamicPropEntityMessage>();

			DynamicProp* prop = new DynamicProp(m->nid);
			prop->setPos(Vec2f(m->x, m->y));
			world.add(prop);
		}
	}

	/*if (type == Server::MESSAGE_TYPE::NEW_PLAYER)
	{
		sf::Uint32 id;
		packet >> id;
		int clientId = id;

		packet >> id;
		int nid = id;

		float x, y;
		packet >> x >> y;

		Player* player = new Player(nid);
		player->setPos(Vec2f(x, y));
		players[clientId] = player;

		Log::debug("Player with id "+std::to_string(nid));

		if (clientId != Client::getClientId())
		{
			player->setRemote(true);
		}
		entities.push_back(std::unique_ptr<Entity>(player));

		return true;
	}*/


	return false;
}


