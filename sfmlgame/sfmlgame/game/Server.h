#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include <SFML\System\Clock.hpp>
#include <functional>
#include "SharedMultiplayer.h"
#include "NetEvent.h"

struct ClientInformation
{
	int id;
	int ping;
	int pingPassword;
	std::shared_ptr<sf::TcpSocket> socket;
	sf::Packet packet;

	bool disconnected;
};

class Server
{
public:
	enum class MESSAGE_TYPE
	{
		SET_CLIENT_ID,
		PING,
		ENTITY_INFO,
		NEW_PLAYER,
		PLAYER_UPDATE,
		IGNORE,
		MESSAGE,
		ENTITY_SPAWN,
		EVENT
	};

	Server();
	~Server();

	static void listen(int port = 27345);
	static void stop();
	static void update(float dt);
	static void onEvent(ClientInformation& client, sf::Packet packet);
	static void send(ClientInformation& client, sf::Packet packet);
	static void sendActually(ClientInformation& client);
	static void send(sf::Packet packet);
	static void send(ClientInformation& client, MultiplayerMessage& message);
	static void send(MultiplayerMessage& message);
	static void send(NetEvent event);
	static bool isServer();
	static int getNewEntityId();
	static void setIsInServer(bool is);
	static bool isInServer();
	static void setGetInfo(std::function<std::vector<sf::Packet>()> f);
	static void setOnNewPlayer(std::function<void(ClientInformation&)> f);
	static void setOnPacket(std::function<bool(ClientInformation&, Server::MESSAGE_TYPE, sf::Packet&)> f);
	static std::vector<ClientInformation>& getClients();
	
private:
	static Server& get();
	sf::TcpListener listener;
	std::vector<ClientInformation> clients;
	sf::SocketSelector selector;
	int socketId;

	float pingTimer;
	sf::Clock pingClock;

	std::function<std::vector<sf::Packet>()> getGameInfo;
	float gameTimer;

	bool isserver;
	bool isInServerVar;

	int lastEntityId;

	std::function<void(ClientInformation&)> onNewPlayer;
	std::function<bool(ClientInformation&, Server::MESSAGE_TYPE, sf::Packet&)> onPacket;
};

