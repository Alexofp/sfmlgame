#pragma once
#include <SFML/Network.hpp>
#include <vector>
#include <memory>

struct ClientInformation
{
	int id;
	std::shared_ptr<sf::TcpSocket> socket;
};

class Server
{
public:
	enum class MESSAGE_TYPE
	{
		SET_CLIENT_ID,
		PING
	};

	Server();
	~Server();

	static void listen(int port = 12345);
	static void update(float dt);
	
private:
	static Server& get();
	sf::TcpListener listener;
	std::vector<ClientInformation> clients;
	sf::SocketSelector selector;
	int socketId;
};

