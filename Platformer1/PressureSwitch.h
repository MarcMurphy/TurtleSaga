#pragma once
#include "BaseObject.h"
#include "SDL_image.h"
#include "Box2D\Box2D.h"
#include <string>
class GameObjects;
class PressureSwitch : public BaseObject
{
public:
	PressureSwitch(b2World*,b2Vec2);
	PressureSwitch(void);
	~PressureSwitch(void);

	void Update();
	b2Vec2 position;
	void setPosition(b2Vec2);
	bool active;
	void setActive(bool);
	b2Body* boxSwitch;

	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* newTexture);
	void render(SDL_Renderer* renderer, SDL_Texture* texture);
};

