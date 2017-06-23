#pragma once
#include "State.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include "Player.h"
#include "Server.h"
#include <unordered_map>
#include "Terrain.h"
#include "GameWorld.h"
#include "Inventory.h"
#include "PlayerInventory.h"
#include "InventoryPanel.h"

struct ClientPlayerInfo
{
	Player* entity;
};

class Game :
	public State
{
public:
	Game(std::string ip = "127.0.0.1");
	~Game();

	void update(float dt);
	void draw();
	void drawUI();
	void resizeGui();
	void handleEvent(sf::Event event);

	void applyGameInfo(sf::Packet& info);
	bool handlePacket(Server::MESSAGE_TYPE type, sf::Packet& packet);
	sf::Packet getClientInfo();
	void loadPlayer(Player* player);

private:
	//std::vector<std::unique_ptr<Entity> > entities;
	std::unordered_map<int, ClientPlayerInfo> players;
	
	GameWorld world;

	float sendGameInfoTimer;

	sf::View guiView;
	PlayerInventory inventoryScreen;
};

