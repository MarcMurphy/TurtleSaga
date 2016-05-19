#pragma once
#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "SDL.h"

class Elevator : BaseObject
{
public:
	Elevator(b2World* world, float body1X,float body1Y, float body1Width,float body1Height, float body1Density,
			float body2X,float body2Y, float body2Width,float body2Height,float body2Density,
			float anchor1X,float anchor1Y,float anchor2X,float anchor2Y);
	~Elevator(void);
	void render(SDL_Renderer*,SDL_Texture*,SDL_Texture*,SDL_Texture*,SDL_Texture*,b2Vec2);
	b2Body* body1;
	b2Body* body2;
	b2Vec2 anchor1;
	b2Vec2 anchor2;
	b2Vec2 size1;
	b2Vec2 size2;
	
	static SDL_Point* rotatePoint;
};

