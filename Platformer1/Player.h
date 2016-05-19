#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"
#include "BaseObject.h"
#include "KeyHandler.h"
#include "SoundManager.h"
class Player : BaseObject
{
public:
	static Player* CreatePlayer(float x,float y,b2World* world);
	Player(float x, float y, b2World* world);
	~Player(void);

	const float mSpeed;
	const float mWidth;
	const float mHeight;
	float mShellStrength;	
	float mLives;
	float mMass;
	
	b2Body* Body;

	void Update(float deltaTime);
	void MoveLeft();
	void MoveRight();
	void Jump();
	bool isBlocking;
	float animationTime;
	bool inAir;
	void render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2);
	float jumpCharge;
	int imgNum;
	int walk[4];
	bool dead;
private:
	float moveForceLevel;
	float jumpForceLevel;
	bool facingRight;
};

