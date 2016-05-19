
#pragma once
#include "Box2D\Box2D.h"
#include "CollisionIdentifier.h"
#include "Game.h"
using namespace std;
class ContactListener: public b2ContactListener
{
public:
	static ContactListener* me;
	static ContactListener* createListener();
	ContactListener(void);
	~ContactListener(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

