#pragma once
#include <Box2D\Box2D.h>

class ContactListener : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener();

	virtual void BeginContact(b2Contact* contact);

	virtual void EndContact(b2Contact* contact);
};

