#pragma once
#include "BaseObject.h"
#include "SDL_image.h"
#include "Box2D\Box2D.h"
#include <string>
class GameObjects;
class PrismaticBox : public BaseObject
{
public:
	PrismaticBox(b2World*,b2Vec2,b2Vec2);
	PrismaticBox(void);
	~PrismaticBox(void);

	b2Vec2 switchPosition;
	b2Vec2 blockPosition;
	b2Body* boxBody1;
	b2Body* boxBody2;

	SDL_Texture* getTexture();
	void render(SDL_Renderer* renderer,SDL_Texture* texture,b2Vec2);
};

