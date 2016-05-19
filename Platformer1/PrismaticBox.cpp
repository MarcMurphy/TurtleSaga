#include "PrismaticBox.h"

PrismaticBox::PrismaticBox(b2World* world,b2Vec2 theBlockPosition1,b2Vec2 theBlockPosition2)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="prismaticBox";
	
	boxBody1 = BodyFactory::createBody(world,theBlockPosition1.x,theBlockPosition1.y,30,30,1.0f,0.2f,true,false,myColIdent,3,1);
	boxBody2 = BodyFactory::createBody(world,theBlockPosition2.x,theBlockPosition2.y,30,30,1.0f,0.2f,true,false,myColIdent,3,1);
	
	/*b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.01f;
	fixtureDef.friction = 0;

	//Box1
	b2PolygonShape box1;
	box1.SetAsBox(30/2.0f, 30/2.0f);
	bodyDef.position.Set(theSwitchPosition.x,theSwitchPosition.y);
	fixtureDef.shape = &box1;
	boxBody1 = world->CreateBody(&bodyDef);
	boxBody1->CreateFixture( &fixtureDef );
  
	//Box2
	b2PolygonShape reactionBlockBox;
	reactionBlockBox.SetAsBox(30/2.0f, 30/2.0f);
	bodyDef.position.Set(theBlockPosition.x,theBlockPosition.y);
	fixtureDef.shape = &reactionBlockBox;
	fixtureDef.density = 2.0f;
	boxBody2 = world->CreateBody(&bodyDef);
	boxBody2->CreateFixture( &fixtureDef );*/

	b2PrismaticJointDef jointDef;
	jointDef.Initialize(boxBody1,boxBody2, b2Vec2(0,0),b2Vec2(0,1));
	b2PrismaticJoint* joint = (b2PrismaticJoint*)world->CreateJoint( &jointDef );
}

void PrismaticBox::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{
	//BaseBody::render(renderer,  TextureManager::getManager()->texturePressureSwitch);
	SDL_Rect stretchRect; 

	stretchRect.x = boxBody1->GetPosition().x-(30/2.0f)-offset.x;
	stretchRect.y = boxBody1->GetPosition().y-(30/2.0f)-offset.y; 
	stretchRect.w = 30; 
	stretchRect.h = 30;

	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 

	stretchRect.x = boxBody2->GetPosition().x-(30/2.0f)-offset.x;
	stretchRect.y = boxBody2->GetPosition().y-(30/2.0f)-offset.y; 
	stretchRect.w = 30; 
	stretchRect.h = 30;

	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 
}

PrismaticBox::PrismaticBox(void)
	:BaseObject()
{
}


PrismaticBox::~PrismaticBox(void)
{
}
