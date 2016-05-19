#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"
#include "BaseObject.h"

class Platform:BaseObject
{
public:
	static Platform* CreatePlatform(float x,float y,float width,float height, b2World* world);
	
	Platform(float x,float y,float width,float height, b2World* world);
	~Platform(void);

	b2Body* Body;
	float mWidth;
	float mHeight;
	void render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2);
	b2PolygonShape Box;
};

