#include "GameServer.h"
#include "Log.h"


GameServer::GameServer()
{
	Server::listen();
	Server::setGetInfo([&]() { return this->getGameInfo(); });
	Server::setOnNewPlayer([&](ClientInformation& id) { this->serverPlayerConnected(id); });
	Server::setOnPacket([&](ClientInformation& info, Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacketServer(info, type, packet); });
}


GameServer::~GameServer()
{
}

void GameServer::update(float dt)
{
	Server::update(dt);

	for (auto& entity : entities)
	{
		entity->update(dt);
	}
}

void GameServer::draw()
{
}

void GameServer::handleEvent(sf::Event event)
{
}

sf::Packet GameServer::getGameInfo()
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

bool GameServer::handlePacketServer(ClientInformation & info, Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::PLAYER_UPDATE)
	{
		//if (info.id != Client::getClientId())
		//{
		players[info.id]->readInformation(packet);
		//}

	}
	return false;
}

void GameServer::serverPlayerConnected(ClientInformation& info)
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
