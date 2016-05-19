#pragma once
#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "SDL.h"
class GearPlatform : BaseObject
{
public:
	static GearPlatform* CreateGear(b2World* world,b2Vec2 posCrank, b2Vec2 sizeCrank, b2Vec2 posPlatform, b2Vec2 sizePlatform, b2Vec2 direction);
	GearPlatform(b2World* world,b2Vec2 posCrank, b2Vec2 sizeCrank, b2Vec2 posPlatform, b2Vec2 sizePlatform, b2Vec2 direction);
	~GearPlatform(void);
	void render(SDL_Renderer*,SDL_Texture* blockTexture,b2Vec2);
	b2Body* body1;
	b2Body* body2;
	b2Body* groundBody;
	CollisionIdentifier* myColIdentPlat;
	b2Vec2 mSizeCrank;
	b2Vec2 mSizePlatform;
	b2GearJoint *gearJoint;
	b2PrismaticJoint *translationJoint;
	b2RevoluteJoint *rotationJoint;
	void rotateClockwise();
	void rotateCounterClockwise();
	void resetVelocities();
};
