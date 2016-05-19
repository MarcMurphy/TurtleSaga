#pragma once
#include <vector>
#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "BodyFactory.h"
#include "SDL.h"
using namespace std;

class Catapult : public BaseObject
{
public:
	Catapult* createCatapult(float x, float y, float width, float height,  b2World* world);
	b2Vec2 getPosition();
	void update();
	void render(SDL_Renderer* renderer, SDL_Texture* textureBase,SDL_Texture* catapultBlock,SDL_Texture* catapultWheel,SDL_Texture* catapultBeam,SDL_Texture* catapultArm, b2Vec2 offset);
	Catapult(float x, float y, float width, float height,  b2World* world);
	~Catapult(void);

	Catapult* m_Catapult;
	b2Vec2 m_Position;
	b2Vec2 m_Dimentions;
	
	
	b2Body* catapultLeaverBody;
	b2Vec2 leaverPosition;
	b2Vec2 leaverDimentions;
	
	b2Body* catapultBaseBody;
	b2Vec2 basePosition;
	b2Vec2 baseDimentions;
	
	b2Body* catapultStopBlockBody;
	b2Vec2 stopBlockPosition;
	b2Vec2 stopBlockDimentions;

	b2Body* catapultAnchorBeamBody;
	b2Vec2 anchorBeamPosition;
	b2Vec2 anchorBeamDimentions;

	b2Body* catapultBackWheelBody;
	b2Body* catapultFrontWheelBody;
	float wheelRadius;

};