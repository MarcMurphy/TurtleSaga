#pragma once
#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "SDL.h"
class ObjectManager;
class BabyTurtle:BaseObject
{
public:
	const float mWidth;
	const float mHeight;
	BabyTurtle(float x,float y, b2World* world);
	~BabyTurtle(void);
	void Update(b2Body*,b2Body* enemyBody,float);
	b2Body* body;
	void render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2);
	float animationTime;
	int imgNum;
	int walk[4];
	bool dead;
};


#include "ObjectManager.h"