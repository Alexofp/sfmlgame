#pragma once
#include <SFML/Network.hpp>
#include <functional>
#include "Server.h"

class Client
{
public:
	Client();
	~Client();

	static void connect(std::string address = "127.0.0.1", int port = 27345);
	static void disconnect();
	static void onEvent(sf::Packet& packet);
	static void update(float dt);
	static void send(sf::Packet packet);
	static void send(NetEvent event);
	static void setOnGameInfo(std::function<void(sf::Packet&)> f);
	static void setOnPacket(std::function<bool(Server::MESSAGE_TYPE, sf::Packet&)> f);
	static int getClientId();
private:
	static Client& get();

	sf::TcpSocket socket;
	int clientid;
	std::function<void(sf::Packet&)> onGameInfo;
	std::function<bool(Server::MESSAGE_TYPE, sf::Packet&)> onPacket;
};

