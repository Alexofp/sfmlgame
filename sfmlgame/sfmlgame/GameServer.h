#pragma once
#include "State.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "Server.h"
#include <unordered_map>

class GameServer :
	public State
{
public:
	GameServer();
	~GameServer();

	void update(float dt);
	void draw();
	void handleEvent(sf::Event event);

	sf::Packet getGameInfo();
	bool handlePacketServer(ClientInformation& info, Server::MESSAGE_TYPE type, sf::Packet& packet);
	void serverPlayerConnected(ClientInformation& info);
private:
	std::vector<std::unique_ptr<Entity> > entities;
	std::unordered_map<int, Player*> players;
};

