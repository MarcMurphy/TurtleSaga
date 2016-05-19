#pragma once
#include "BaseObject.h"
#include "SDL_image.h"
#include "Box2D\Box2D.h"
#include <string>
#include <vector>
class GameObjects;
class Bridge : public BaseObject
{
public:
	Bridge(b2World*,b2Vec2,int,float);
	Bridge(void);
	~Bridge(void);

	b2WeldJointDef weldJoint;
	b2Body* Anchor;
	vector<b2Body*> Planks;
	float size;

	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* newTexture);
	void render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2);
};
