#ifndef PUSHABLE_BLOCK_H
#define PUSHABLE_BLOCK_H

#include "Box2D/Box2D.h"
#include "SDL_image.h"
#include "BaseObject.h"

class PushableBlock: public BaseObject{
private:
	b2Vec2 m_position;
	
public:
	b2Body* body;
	float mWidth;
	float mHeight;
	PushableBlock(float x,float y, float width, float height, float density, b2World* world);
	void render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset);
};
#endif PUSHABLE_BLOCK_H








