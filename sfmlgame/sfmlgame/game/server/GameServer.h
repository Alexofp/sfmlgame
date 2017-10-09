#pragma once
#include "State.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "Server.h"
#include <unordered_map>
#include "GameWorld.h"

struct ServerPlayerInfo
{
	Player* entity;
};

class GameServer :
	public State
{
public:
	GameServer();
	~GameServer();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	std::vector<sf::Packet> getGameInfo();
	bool handlePacketServer(ClientInformation& info, Server::MESSAGE_TYPE type, sf::Packet& packet);
	void serverPlayerConnected(ClientInformation& info);
private:
	GameWorld world;
	std::unordered_map<int, ServerPlayerInfo> players;
};

