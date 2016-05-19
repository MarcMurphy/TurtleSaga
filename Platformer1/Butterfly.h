#include "Player.h"
//#include "Tree.h"
#include "SDL.h"
#include "Box2D\Box2D.h"
#include "BaseObject.h"
class ObjectManager;
#pragma once
class Butterfly: BaseObject
{
public:
	static Butterfly* CreateButterfly(float x,  float y, Player* player,b2World* world);
	Butterfly(float x, float y, Player* player,b2World* world);
	~Butterfly(void);
	Player* player;
	b2Body* Body;
	void render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* texture2, SDL_Texture* texture3,b2Vec2 offset);

	const float mWidth;
	const float mHeight;
	b2World* mWorld;
	void Update(float deltaTime);
	float mTotalTime;
	const float mTimeBetweenShots;
	//Tree* CreateTree(float x,float y, float strength);
	float health;
	int animationTimer;
	int frame;
	const int numFrames;
};

#include "ObjectManager.h"