#pragma once
#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	static void connect(std::string address = "127.0.0.1", int port = 12345);
	static void onEvent(sf::Packet& packet);
	static void update(float dt);
private:
	static Client& get();

	sf::TcpSocket socket;
	int clientid;
};

