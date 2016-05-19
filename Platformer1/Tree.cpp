#include "Tree.h"

SDL_Point* Tree::pBot = new SDL_Point();
SDL_Point* Tree::pMid = new SDL_Point();
SDL_Point* Tree::pTop = new SDL_Point();

Tree::Tree(float scale,b2Vec2 position, float strength, Player* player,b2World* world, b2Vec2 speed):
mScale(scale),
mStrength(strength),
mPosition(position),
mpPlayer(player),
mImageSize(b2Vec2(117,273)), 
mTreeBotImaSize(b2Vec2(75,170)),
mTreeMidImaSize(b2Vec2(94,178)),
mTreeTopImaSize(b2Vec2(53,97)),
mpWorld(world),
mJointsAlive(true),
mDestroyJoints(false)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="tree";
	
	Tree::pBot->x=0;
	Tree::pMid->x=0;
	Tree::pTop->x=0;

	
	Tree::pBot->y=0;
	Tree::pMid->y=0;
	Tree::pTop->y=0;








	b2Vec2 lTreeBotVerticies[7];
	b2Vec2 lTreeMidVerticies[7];
	b2Vec2 lTreeTopVerticies[4];

	lTreeBotVerticies[0].Set(44*mScale,169*mScale); 
	lTreeBotVerticies[1].Set(62*mScale,169*mScale);
	lTreeBotVerticies[2].Set(62*mScale,125*mScale);
	lTreeBotVerticies[3].Set(74*mScale,115*mScale);
	lTreeBotVerticies[4].Set(17*mScale,0);
  	lTreeBotVerticies[5].Set(0,120*mScale);
	lTreeBotVerticies[6].Set(45*mScale,128*mScale);

	lTreeMidVerticies[0].Set(71*mScale,177*mScale); 
	lTreeMidVerticies[1].Set(93*mScale,174*mScale);
	lTreeMidVerticies[2].Set(63*mScale,66*mScale);
	lTreeMidVerticies[3].Set(63*mScale,18*mScale);
	lTreeMidVerticies[4].Set(53*mScale,2*mScale);
	lTreeMidVerticies[5].Set(0,52*mScale);
	lTreeMidVerticies[6].Set(54*mScale,164*mScale);


	lTreeTopVerticies[0].Set(0,95*mScale); 
	lTreeTopVerticies[1].Set(53*mScale,47*mScale);
	lTreeTopVerticies[2].Set(0,33*mScale);
	lTreeTopVerticies[3].Set(1*mScale,56*mScale);




	b2FixtureDef ltreeBotFixDef;
	b2FixtureDef ltreeMidFixDef;
	b2FixtureDef ltreeTopFixDef;
	
	ltreeBotFixDef.filter.categoryBits = 4;
	ltreeBotFixDef.filter.maskBits = 3;
	ltreeMidFixDef.filter.categoryBits = 4;
	ltreeMidFixDef.filter.maskBits = 3;
	ltreeTopFixDef.filter.categoryBits = 4;
	ltreeTopFixDef.filter.maskBits = 3;
	ltreeBotFixDef.density=1;
	ltreeMidFixDef.density=1;
	ltreeTopFixDef.density=1;

	b2BodyDef ltreeBotBodyDef;
	b2BodyDef ltreeMidBodyDef;
	b2BodyDef ltreeTopBodyDef;
	ltreeBotBodyDef.type = b2_dynamicBody;
	ltreeBotBodyDef.userData = myColIdent;
	ltreeMidBodyDef.type = b2_dynamicBody;
	ltreeMidBodyDef.userData = myColIdent;
	ltreeTopBodyDef.type = b2_dynamicBody;
	ltreeTopBodyDef.userData = myColIdent;

	b2PolygonShape lpolyTreeBotShape;
	b2PolygonShape lpolyTreeMidShape;
	b2PolygonShape lpolyTreeTopShape;
	lpolyTreeBotShape.Set(lTreeBotVerticies, 7);
	lpolyTreeMidShape.Set(lTreeMidVerticies, 7);
	lpolyTreeTopShape.Set(lTreeTopVerticies, 4);


	ltreeBotFixDef.shape = &lpolyTreeBotShape; 
	ltreeMidFixDef.shape = &lpolyTreeMidShape; 
	ltreeTopFixDef.shape = &lpolyTreeTopShape; 

	ltreeBotBodyDef.position.Set(position.x,position.y);
	ltreeMidBodyDef.position.Set(position.x+45,position.y);
	ltreeTopBodyDef.position.Set(position.x+90,position.y);

	mTreeBotBody = world->CreateBody(&ltreeBotBodyDef);
	mTreeMidBody = world->CreateBody(&ltreeMidBodyDef);
	mTreeTopBody = world->CreateBody(&ltreeTopBodyDef);

	mTreeBotBody->CreateFixture(&ltreeBotFixDef); 
	mTreeMidBody->CreateFixture(&ltreeMidFixDef); 
	mTreeTopBody->CreateFixture(&ltreeTopFixDef); 

	b2WeldJointDef lBotMid;
	b2WeldJointDef lMidTop;

	lBotMid.bodyA = mTreeBotBody;
	lBotMid.bodyB = mTreeMidBody;
	lBotMid.collideConnected = false;
	lBotMid.localAnchorB = b2Vec2(0,0);
	lBotMid.localAnchorA = b2Vec2(16*mScale,-53*mScale);


	lMidTop.bodyA = mTreeMidBody;
	lMidTop.bodyB = mTreeTopBody;
	lMidTop.collideConnected = false;

	lMidTop.localAnchorA = b2Vec2(1*mScale,-46*mScale);


	mBotMidjoint = (b2WeldJoint*)world->CreateJoint(&lBotMid);
	mMidTopjoint = (b2WeldJoint*)world->CreateJoint(&lMidTop);


	mTreeMidBody->ApplyForceToCenter(speed,true);
	mTreeMidBody->SetGravityScale(0);
	mTreeBotBody->SetGravityScale(0);
	mTreeTopBody->SetGravityScale(0);
}

void Tree::Update(float time)
{
	if(mDestroyJoints && mJointsAlive){
		DestroyJoints();
		mDestroyJoints = false;
		mTreeMidBody->SetGravityScale(1);
		mTreeBotBody->SetGravityScale(1);
		mTreeTopBody->SetGravityScale(1);
	}
	if(mJointsAlive)
	{
		b2Vec2 dif = mpPlayer->Body->GetPosition()-mTreeTopBody->GetPosition();
		{
			dif.x *= 5;
			dif.y *= 5;
			mTreeTopBody->ApplyLinearImpulse(dif,mTreeTopBody->GetPosition(),true);
		}
	}
}

void Tree::Draw(SDL_Renderer* renderer,  SDL_Texture* textureBot,  SDL_Texture* textureMid,  SDL_Texture* textureTop,b2Vec2 offset){
	SDL_Rect stretchBotRect; 
	SDL_Rect stretchMidRect; 
	SDL_Rect stretchTopRect; 
	float rotationBot;
	float rotationMid;
	float rotationTop;

	// Draw Bottom
	stretchBotRect.x = mTreeBotBody->GetPosition().x-offset.x; 
	stretchBotRect.y = mTreeBotBody->GetPosition().y-offset.y; 
	stretchBotRect.w = mTreeBotImaSize.x*mScale; 
	stretchBotRect.h = mTreeBotImaSize.y*mScale;

	rotationBot = (mTreeBotBody->GetAngle()*180.0/3.14159265);
	SDL_RenderCopyEx ( renderer, textureBot, NULL, &stretchBotRect, rotationBot,pBot , SDL_RendererFlip::SDL_FLIP_NONE );


	// Draw Middle
	stretchMidRect.x = mTreeMidBody->GetPosition().x-offset.x; 
	stretchMidRect.y = mTreeMidBody->GetPosition().y-offset.y; 
	stretchMidRect.w = mTreeMidImaSize.x*mScale; 
	stretchMidRect.h = mTreeMidImaSize.y*mScale;
	rotationMid = (mTreeMidBody->GetAngle()*180.0/3.14159265);
	SDL_RenderCopyEx ( renderer, textureMid, NULL, &stretchMidRect, rotationMid, pMid, SDL_RendererFlip::SDL_FLIP_NONE );

	// Draw Top
	stretchTopRect.x = mTreeTopBody->GetPosition().x-offset.x; 
	stretchTopRect.y = mTreeTopBody->GetPosition().y-offset.y; 
	stretchTopRect.w = mTreeTopImaSize.x*mScale; 
	stretchTopRect.h = mTreeTopImaSize.y*mScale;
	rotationTop = (mTreeTopBody->GetAngle()*180.0/3.14159265);
	SDL_RenderCopyEx ( renderer, textureTop, NULL, &stretchTopRect, rotationTop, pTop, SDL_RendererFlip::SDL_FLIP_NONE );
	

}


void Tree::DestroyJoints(){
	if(mJointsAlive){
		mpWorld->DestroyJoint(mBotMidjoint);
		mpWorld->DestroyJoint(mMidTopjoint);
		mJointsAlive = false;
		SoundManager::getSoundManager()->playTreeShatter();
	}
}
