#include "SharedMultiplayer.h"

MultiplayerMessage::MultiplayerMessage(MessageType type)
{
	this->type = type;
}

MultiplayerMessage::MultiplayerMessage(sf::Packet & packet)
{
	read(packet);
}

MessageType MultiplayerMessage::getType()
{
	return type;
}

void MultiplayerMessage::read(sf::Packet & packet)
{
	sf::Uint8 messageType;
	packet >> messageType;
	type = (MessageType)messageType;

	if (type == MessageType::PlayerUpdate)
	{
		PlayerUpdateMessage* mes = new PlayerUpdateMessage();
		message = std::unique_ptr<MessageBase>(mes);
		
		packet >> mes->x >> mes->y >> mes->ang >> mes->speedx >> mes->speedy >> mes->lookx >> mes->looky;
	}
	if (type == MessageType::HumanAiUpdate)
	{
		HumanAiUpdateMessage* mes = new HumanAiUpdateMessage();
		message = std::unique_ptr<MessageBase>(mes);

		packet >> mes->x >> mes->y >> mes->ang >> mes->speedx >> mes->speedy >> mes->lookx >> mes->looky;
	}
	if (type == MessageType::SpawnPlayerEntity)
	{
		SpawnPlayerEntityMessage* mes = new SpawnPlayerEntityMessage();
		message = std::unique_ptr<MessageBase>(mes);

		packet >> mes->nid >> mes->playerId >> mes->x >> mes->y;
	}
	if (type == MessageType::SpawnHumanAiEntity)
	{
		SpawnHumanAiEntityMessage* mes = new SpawnHumanAiEntityMessage();
		message = std::unique_ptr<MessageBase>(mes);

		packet >> mes->nid >> mes->x >> mes->y;
	}
	if (type == MessageType::DynamicPropUpdate)
	{
		DynamicPropUpdateMessage* mes = new DynamicPropUpdateMessage();
		message = std::unique_ptr<MessageBase>(mes);

		packet >> mes->x >> mes->y >> mes->ang;
	}
	if (type == MessageType::SpawnDynamicPropEntity)
	{
		SpawnDynamicPropEntityMessage* mes = new SpawnDynamicPropEntityMessage();
		message = std::unique_ptr<MessageBase>(mes);

		packet >> mes->nid >> mes->x >> mes->y;
	}
}

void MultiplayerMessage::write(sf::Packet & packet)
{
	sf::Uint8 messageType = (sf::Uint8)type;
	packet << messageType;

	if (type == MessageType::PlayerUpdate)
	{
		PlayerUpdateMessage* mes = (PlayerUpdateMessage*)message.get();

		packet << mes->x << mes->y << mes->ang << mes->speedx << mes->speedy << mes->lookx << mes->looky;
	}
	if (type == MessageType::HumanAiUpdate)
	{
		HumanAiUpdateMessage* mes = (HumanAiUpdateMessage*)message.get();

		packet << mes->x << mes->y << mes->ang << mes->speedx << mes->speedy << mes->lookx << mes->looky;
	}
	if (type == MessageType::SpawnPlayerEntity)
	{
		SpawnPlayerEntityMessage* mes = (SpawnPlayerEntityMessage*)message.get();

		packet << mes->nid << mes->playerId << mes->x << mes->y;
	}
	if (type == MessageType::SpawnHumanAiEntity)
	{
		SpawnHumanAiEntityMessage* mes = (SpawnHumanAiEntityMessage*)message.get();

		packet << mes->nid << mes->x << mes->y;
	}
	if (type == MessageType::DynamicPropUpdate)
	{
		DynamicPropUpdateMessage* mes = (DynamicPropUpdateMessage*)message.get();

		packet << mes->x << mes->y << mes->ang;
	}
	if (type == MessageType::SpawnDynamicPropEntity)
	{
		SpawnDynamicPropEntityMessage* mes = (SpawnDynamicPropEntityMessage*)message.get();

		packet << mes->nid << mes->x << mes->y;
	}
}

void MultiplayerMessage::setMessage(MessageBase * m)
{
	message = std::unique_ptr<MessageBase>(m);
}

PlayerUpdateMessage::PlayerUpdateMessage()
{
	x = 0.f;
	y = 0.f;
	ang = 0.f;
}

PlayerUpdateMessage::PlayerUpdateMessage(float x, float y, float ang, float speedx, float speedy, float lookx, float looky)
{
	this->x = x;
	this->y = y;
	this->ang = ang;
	this->speedx = speedx;
	this->speedy = speedy;
	this->lookx = lookx;
	this->looky = looky;
}

SpawnPlayerEntityMessage::SpawnPlayerEntityMessage()
{
	x = 0.f;
	y = 0.f;
}

SpawnPlayerEntityMessage::SpawnPlayerEntityMessage(int nid, int playerId, float x, float y)
{
	this->x = x;
	this->y = y;
	this->playerId = playerId;
	this->nid = nid;
}

DynamicPropUpdateMessage::DynamicPropUpdateMessage()
{
	x = 0.f;
	y = 0.f;
	ang = 0.f;
}

DynamicPropUpdateMessage::DynamicPropUpdateMessage(float x, float y, float ang)
{
	this->x = x;
	this->y = y;
	this->ang = ang;
}

SpawnDynamicPropEntityMessage::SpawnDynamicPropEntityMessage()
{
	x = 0.f;
	y = 0.f;
	nid = 0;
}

SpawnDynamicPropEntityMessage::SpawnDynamicPropEntityMessage(int nid, float x, float y)
{
	this->x = x;
	this->y = y;
	this->nid = nid;
}

HumanAiUpdateMessage::HumanAiUpdateMessage()
{

}

HumanAiUpdateMessage::HumanAiUpdateMessage(float x, float y, float ang, float speedx, float speedy, float lookx, float looky)
{
	this->x = x;
	this->y = y;
	this->ang = ang;
	this->speedx = speedx;
	this->speedy = speedy;
	this->lookx = lookx;
	this->looky = looky;
}

SpawnHumanAiEntityMessage::SpawnHumanAiEntityMessage()
{
}

SpawnHumanAiEntityMessage::SpawnHumanAiEntityMessage(int nid, float x, float y)
{
	this->x = x;
	this->y = y;
	this->nid = nid;
}
