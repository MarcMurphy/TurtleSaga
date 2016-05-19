#pragma once
#include "Box2D\Box2D.h"
#include "CollisionIdentifier.h"
class BodyFactory
{
public:
	BodyFactory(void);
	~BodyFactory(void);
	static b2Body* createBody(b2World* world, float x, float y,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent,
								int16 categoryBits, int16 maskBits);
};

