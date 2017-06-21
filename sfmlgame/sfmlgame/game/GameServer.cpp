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

	for (int i = 0; i < 100; i++)
	{
		DynamicProp* prop = new DynamicProp();
		prop->setPos(Vec2f(100.f+rand()%200, 100.f + rand() % 200));
		world.add(prop);

		HumanAi* asd = new HumanAi();
		asd->setPos(Vec2f(500.f + rand() % 5000, 500.f + rand() % 5000));
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
	Server::setIsInServer(true);
	Server::update(dt);
	world.update(dt);
	world.physicsUpdate(dt);
	Server::setIsInServer(false);
}

void GameServer::draw()
{
	//world.getPhysicsWorld().debugDraw();
}

void GameServer::handleEvent(sf::Event event)
{
}

std::vector<sf::Packet> GameServer::getGameInfo()
{
	std::vector<sf::Packet> packets;
	packets.reserve(world.getEntities().size());

	for (auto& entity : world.getEntities())
	{
		sf::Packet packet;
		packet << (sf::Uint8)Server::MESSAGE_TYPE::ENTITY_INFO;

		packet << (sf::Uint32)entity->getNid();
		entity->writeInformation(packet);
		packets.push_back(packet);
	}

	return packets;
}

bool GameServer::handlePacketServer(ClientInformation & info, Server::MESSAGE_TYPE type, sf::Packet & packet)
{
	if (type == Server::MESSAGE_TYPE::MESSAGE)
	{
		players[info.id].entity->readInformation(packet);
	}
	else if (type == Server::MESSAGE_TYPE::EVENT)
	{
		sf::Packet newpacket;
		//newpacket << (sf::Uint8)Server::MESSAGE_TYPE::EVENT;
		newpacket.append(packet.getData(), packet.getDataSize());
		Server::send(newpacket);

		int from, to;
		std::string eventType;
		packet >> from >> to >> eventType;
		
		Entity* ent = world.findEntity(to);
		if (ent != 0)
		{
			ent->handleEvent(from, eventType, packet);
		}
	}
	return false;
}

void GameServer::serverPlayerConnected(ClientInformation& info)
{
	int clientId = info.id;
	float x = 950.f, y = 950.f;

	Player* player = new Player();
	player->setClientId(clientId);
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

		sf::Packet packet;
		packet << (sf::Uint8)Server::MESSAGE_TYPE::ENTITY_SPAWN;
		packet << (sf::Uint8)entityPtr->getType();
		packet << (sf::Uint32)entityPtr->getNid();
		entityPtr->writeSpawn(packet);

		Server::send(info, packet);
	}

	sf::Packet packet;
	packet << (sf::Uint8)Server::MESSAGE_TYPE::ENTITY_SPAWN;
	packet << (sf::Uint8)player->getType();
	packet << (sf::Uint32)player->getNid();
	player->writeSpawn(packet);
	Server::send(packet);

	Log::debug("its ok");
}
