#include "Game.h"
#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Log.h"

Game::Game():State()
{
	auto* player = new Player();
	player->setPos(Vec2f(50, 50));
	entities.push_back(std::unique_ptr<Entity>(player));

	Server::listen();
	Server::setGetInfo([&]() { return this->getGameInfo(); });
	Server::setOnNewPlayer([&](ClientInformation& id) { this->serverPlayerConnected(id); });
	Server::setOnPacket([&](ClientInformation& info,Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacketServer(info, type, packet); });

	Client::connect("89.252.88.219");
	Client::setOnGameInfo([&](sf::Packet& packet) { this->applyGameInfo(packet); });
	Client::setOnPacket([&](Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacket(type, packet); });
}


Game::~Game()
{
}

void Game::update(float dt)
{
	Server::update(dt);
	Client::update(dt);

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

Entity* Game::findEntity(int nid)
{
	for (auto& entity: entities)
	{
		if (entity->getNid() == nid)
			return entity.get();
	}

	return nullptr;
}

sf::Packet Game::getClientInfo()
{
	sf::Packet packet;
	if (Client::getClientId() != -1)
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::PLAYER_UPDATE;
		players[Client::getClientId()]->writeInformation(packet);
	}
	else
	{
		packet << (sf::Uint8)Server::MESSAGE_TYPE::IGNORE;
	}
	
	return packet;
}

sf::Packet Game::getGameInfo()
{
	sf::Packet packet;
	packet << (sf::Uint8)Server::MESSAGE_TYPE::ENTITY_INFO;
	packet << (sf::Uint16)entities.size();
	for (auto& entity : entities)
	{
		packet << (sf::Uint32)entity->getNid();
		packet << (sf::Uint8)entity->getSyncType();
		entity->writeInformation(packet);
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

		sf::Uint8 syncType;
		info >> syncType;

		Entity* ent = findEntity(id);
		//Entity* ent = players[id];
		if (ent == 0 || id == players[Client::getClientId()]->getNid())
		{
			Entity::SyncType type = (Entity::SyncType)syncType;
			if (type == Entity::SyncType::Entity)
			{
				float x, y, w, h, ang;
				info >> x >> y >> w >> h >> ang;

				if (ent == 0)
					Log::debug("No entity found with nid " + std::to_string(id));
			}else
			if (type == Entity::SyncType::Player)
			{
				float x, y, ang;
				info >> x >> y >> ang;

				if (ent == 0)
					Log::debug("No entity found with nid " + std::to_string(id));
			}
			else
			{
				Log::err("Something is very wrong "+std::to_string(count));
			}
		}
		else
		{
			//Log::debug("its ok");
			ent->readInformation(info);
		}
	}

	Client::send(getClientInfo());
}

bool Game::handlePacket(Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::NEW_PLAYER)
	{
		sf::Uint32 id;
		packet >> id;
		int clientId = id;

		packet >> id;
		int nid = id;

		float x, y;
		packet >> x >> y;

		if (!Server::isServer())
		{
			Player* player = new Player(nid);
			player->setPos(Vec2f(x, y));
			players[clientId] = player;

			if (clientId != Client::getClientId())
			{
				player->setRemote(true);
			}

			entities.push_back(std::unique_ptr<Entity>(player));
		}
		else
		{
			if (clientId == Client::getClientId())
			{
				players[clientId]->setRemote(false);
			}
			
		}

		return true;
	}


	return false;
}

bool Game::handlePacketServer(ClientInformation & info, Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::PLAYER_UPDATE)
	{
		if (info.id != Client::getClientId())
		{
			players[info.id]->readInformation(packet);
		}
		
	}
	return false;
}

void Game::serverPlayerConnected(ClientInformation& info)
{
	int clientId = info.id;
	float x = 50.f, y = 50.f;

	Player* player = new Player();
	player->setPos(Vec2f(x, y));
	entities.push_back(std::unique_ptr<Entity>(player));
	player->setRemote(true);

	players[info.id] = player;

	for (auto& client : Server::getClients())
	{
		if (client.id != info.id)
		{
			sf::Packet packet;
			packet << (sf::Uint8)Server::MESSAGE_TYPE::NEW_PLAYER << (sf::Uint32)client.id << (sf::Uint32)players[client.id]->getNid() << players[client.id]->getPos().x << players[client.id]->getPos().y;
			Server::send(info, packet);
		}
	}

	sf::Packet packet;
	packet << (sf::Uint8)Server::MESSAGE_TYPE::NEW_PLAYER << (sf::Uint32)clientId << (sf::Uint32)player->getNid() << x << y;
	Server::send(packet);
	Log::debug("its ok");
}
