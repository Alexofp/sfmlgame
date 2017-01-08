#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "Server.h"
#include <unordered_map>

class Game :
	public State
{
public:
	Game();
	~Game();

	void update(float dt);
	void draw();

	Entity* findEntity(int nid);
	sf::Packet getGameInfo();
	void applyGameInfo(sf::Packet& info);
	bool handlePacket(Server::MESSAGE_TYPE type, sf::Packet& packet);
	bool handlePacketServer(ClientInformation& info, Server::MESSAGE_TYPE type, sf::Packet& packet);
	void serverPlayerConnected(ClientInformation& info);
	sf::Packet getClientInfo();

private:
	std::vector<std::unique_ptr<Entity> > entities;
	std::unordered_map<int, Player*> players;
};

