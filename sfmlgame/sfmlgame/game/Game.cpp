#include "Game.h"
#include "Player.h"
#include "Client.h"
#include "Server.h"
#include "Log.h"

Game::Game():State()
{
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

	for (auto& entity : entities)
	{
		entity->localUpdate(dt);
	}
}

void Game::draw()
{
	terrain.draw();
	for (auto& entity : entities)
	{
		entity->draw();
	}
}

void Game::handleEvent(sf::Event event)
{
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
	}


	return false;
}


