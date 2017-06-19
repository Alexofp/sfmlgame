#include "GameServer.h"
#include "Log.h"
#include "DynamicProp.h"
#include "HumanAi.h"

GameServer::GameServer()
{
	Server::listen();
	Server::setGetInfo([&]() { return this->getGameInfo(); });
	Server::setOnNewPlayer([&](ClientInformation& id) { this->serverPlayerConnected(id); });
	Server::setOnPacket([&](ClientInformation& info, Server::MESSAGE_TYPE type, sf::Packet& packet) { return this->handlePacketServer(info, type, packet); });

	for (int i = 0; i < 10; i++)
	{
		DynamicProp* prop = new DynamicProp();
		prop->setPos(Vec2f(100.f+rand()%200, 100.f + rand() % 200));
		world.add(prop);

		HumanAi* asd = new HumanAi();
		asd->setPos(Vec2f(500.f + rand() % 200, 500.f + rand() % 200));
		world.add(asd);
	}


	world.loadMap("map1");

	//world.addObject("penek", Vec2f(450.f, 100.f));
}


GameServer::~GameServer()
{
}

void GameServer::update(float dt)
{
	Server::update(dt);
	world.update(dt);
	world.physicsUpdate(dt);
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
	packet << (sf::Uint16)world.getEntities().size();
	for (auto& entity : world.getEntities())
	{
		packet << (sf::Uint32)entity->getNid();
		//packet << (sf::Uint8)entity->getSyncType();
		packet << (sf::Uint8)entity->getType();
		auto message = entity->writeInformation();
		message.write(packet);
	}

	return packet;
}

bool GameServer::handlePacketServer(ClientInformation & info, Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::MESSAGE)
	{
		MultiplayerMessage message(packet);

		players[info.id].entity->readInformation(message);

	}
	return false;
}

void GameServer::serverPlayerConnected(ClientInformation& info)
{
	int clientId = info.id;
	float x = 950.f, y = 950.f;

	Player* player = new Player(clientId);
	player->setPos(Vec2f(x, y));
	world.add(player);
	player->setRemote(true);

	ServerPlayerInfo playerinfo;
	playerinfo.entity = player;

	players[info.id] = playerinfo;

	/*for (auto& client : Server::getClients())
	{
		if (client.id != info.id)
		{
			MultiplayerMessage message = players[client.id].entity->spawnMessage();
			Server::send(info, message);
		}
	}*/

	for (auto& entityPtr : world.getEntities())
	{
		if (entityPtr.get() == player)
			continue;

		MultiplayerMessage message = entityPtr->spawnMessage();
		Server::send(info, message);
	}

	MultiplayerMessage message = player->spawnMessage();
	Server::send(message);

	Log::debug("its ok");
}
