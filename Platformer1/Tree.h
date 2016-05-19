// h

#ifndef TREE_H
#define TREE_H

#include "Box2D/Box2D.h"
#include "Player.h"
#include "BaseObject.h"
#include "TextureManager.h"
using namespace std;
class Tree: public BaseObject{
private:
	b2Vec2 mPosition;
	b2Vec2 mVelocity;
	float mStrength;
	Player* mpPlayer;

	SDL_Texture mTexture();
	b2World* mpWorld;

	float mWidth;
	float mHeight;
	b2Vec2 mImageSize;
	float mScale; 

	b2Vec2 mTreeBotImaSize;
	b2Vec2 mTreeMidImaSize;
	b2Vec2 mTreeTopImaSize;

	bool mJointsAlive;


public:
	Tree(float,b2Vec2, float, Player*,b2World* world,b2Vec2 speed);
	void Update(float);
	void Draw(SDL_Renderer* renderer,  SDL_Texture* textureBot,  SDL_Texture* textureMid,  SDL_Texture* textureTop,b2Vec2 offset);
	
	b2Body * mBody;

	b2WeldJoint* mBotMidjoint;
	b2WeldJoint* mMidTopjoint;

	b2Body * mTreeBotBody;
	b2Body * mTreeMidBody;
	b2Body * mTreeTopBody;

	bool mDestroyJoints;
	void DestroyJoints();

	
	static SDL_Point* pBot;
	static SDL_Point* pMid; 
	static SDL_Point* pTop; 
};



#endif TREE_H




