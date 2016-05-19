#ifndef NEST_H
#define NEST_H

#include "Box2D/Box2D.h"
#include "BaseObject.h"
#include "SDL.h"
class Player;
class BabyTurtle;
class Nest: public BaseObject{
private:
	b2Vec2 m_position;

	b2Vec2 mSizeWithEgg;
	b2Vec2 mSizeWithoutEgg;
	float mScale;
	float mRadius;

	Player* mPlayer;

public:
	Nest(b2Vec2,float,b2World* world,Player*);
	BabyTurtle* MakeBaby(b2World* world);
	void Draw(SDL_Renderer*, SDL_Texture* textureNormal,  SDL_Texture* textureHatched, b2Vec2);
	void Update(float);

	b2Body* mBody;

	bool mHatchEgg;
	bool mEggHatched;
};

#endif NEST_H

#include "BabyTurtle.h"
#include "Player.h"




