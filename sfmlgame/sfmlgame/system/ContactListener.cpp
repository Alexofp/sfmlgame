#include "ContactListener.h"
#include "PhysicsWorld.h"
#include "PhysicsCallbacks.h"

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	PhysicsBody* body1 = 0;
	PhysicsBody* body2 = 0;

	if (bodyUserData1)
	{
		body1 = static_cast<PhysicsBody*>(bodyUserData1);
	}
	if (bodyUserData2)
	{
		body2 = static_cast<PhysicsBody*>(bodyUserData2);
	}

	if (body1)
	{
		if (body1->getTag())
		{
			PhysicsCallbacks* callbacks = static_cast<PhysicsCallbacks*>(body1->getTag());
			callbacks->startContact(body2);
		}
	}

	if (body2)
	{
		if (body2->getTag())
		{
			PhysicsCallbacks* callbacks = static_cast<PhysicsCallbacks*>(body2->getTag());
			callbacks->startContact(body1);
		}
	}
}

void ContactListener::EndContact(b2Contact * contact)
{
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

	PhysicsBody* body1 = 0;
	PhysicsBody* body2 = 0;

	if (bodyUserData1)
	{
		body1 = static_cast<PhysicsBody*>(bodyUserData1);
	}
	if (bodyUserData2)
	{
		body2 = static_cast<PhysicsBody*>(bodyUserData2);
	}

	if (body1)
	{
		if (body1->getTag())
		{
			PhysicsCallbacks* callbacks = static_cast<PhysicsCallbacks*>(body1->getTag());
			callbacks->endContact(body2);
		}
	}

	if (body2)
	{
		if (body2->getTag())
		{
			PhysicsCallbacks* callbacks = static_cast<PhysicsCallbacks*>(body2->getTag());
			callbacks->endContact(body1);
		}
	}
}
