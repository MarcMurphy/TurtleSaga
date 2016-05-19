#pragma once
#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "SDL.h"
class Rope : BaseObject
{
public:
	Rope(b2World* world,b2Vec2 pos1,b2Vec2 size1,b2Vec2 pos2,b2Vec2 size2,float ropeLength);
	~Rope(void);

	void render(SDL_Renderer*,SDL_Texture* blockTexture,SDL_Texture* ropeTexture,b2Vec2);
	b2Body* body1;
	b2Body* body2;
	b2RopeJoint *ropeJoint;
	
	b2Vec2 mPos1;
	b2Vec2 mSize1;
	b2Vec2 mPos2;
	b2Vec2 mSize2;
	b2Vec2 mAnchor1;
	b2Vec2 mAnchor2;
	float mMaxLength;
	
	static SDL_Point* rotatePoint;
};

