#pragma once
#include <SFML/Network.hpp>
#include <memory>

enum class MessageType
{
	NoMessage,
	PlayerUpdate,
	SpawnPlayerEntity,
	DynamicPropUpdate,
	SpawnDynamicPropEntity
};

struct MessageBase
{
};

struct MultiplayerMessage
{
	MultiplayerMessage(MessageType type);
	MultiplayerMessage(sf::Packet& packet);

	MessageType type;
	std::unique_ptr<MessageBase> message;

	MessageType getType();
	void read(sf::Packet& packet);
	void write(sf::Packet& packet);
	void setMessage(MessageBase* m);
	template<typename T>
	T* getMessage()
	{
		return (T*)message.get();
	}
};

struct PlayerUpdateMessage : public MessageBase
{
	float x;
	float y;
	float ang;
	float speedx;
	float speedy;

	PlayerUpdateMessage();
	PlayerUpdateMessage(float x, float y, float ang, float speedx, float speedy);
};

struct SpawnPlayerEntityMessage : public MessageBase
{
	float x;
	float y;
	sf::Uint16 nid;
	sf::Uint16 playerId;

	SpawnPlayerEntityMessage();
	SpawnPlayerEntityMessage(int nid, int playerId, float x, float y);
};

struct DynamicPropUpdateMessage : public MessageBase
{
	float x;
	float y;
	float ang;

	DynamicPropUpdateMessage();
	DynamicPropUpdateMessage(float x, float y, float ang);
};

struct SpawnDynamicPropEntityMessage : public MessageBase
{
	float x;
	float y;
	sf::Uint16 nid;

	SpawnDynamicPropEntityMessage();
	SpawnDynamicPropEntityMessage(int nid, float x, float y);
};