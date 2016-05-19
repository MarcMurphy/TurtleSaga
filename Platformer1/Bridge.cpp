#include "Bridge.h"
#include <vector>

Bridge::Bridge(b2World* world,b2Vec2 thePosition, int numberOfPlanks, float theSize)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="bridge";
	Anchor = BodyFactory::createBody(world,thePosition.x,thePosition.y,size,5,1,0.25f,false,false,myColIdent,3,1);
	
	size = theSize;
	/*b2BodyDef bodyDef;
	//bodyDef.fixedRotation = true;
	b2FixtureDef fixtureDef;

	//Anchor
	//fixtureDef.density = 20000.0f;
	bodyDef.type = b2_staticBody;
	b2PolygonShape box1;
	box1.SetAsBox(size/2,5/2.0f);
	bodyDef.position.Set(thePosition.x,thePosition.y);
	fixtureDef.shape = &box1;
	Anchor = world->CreateBody(&bodyDef);
	Anchor->CreateFixture( &fixtureDef );*/
  

	//Planks
	
	//fixtureDef.density = 1.0f;
	//bodyDef.type = b2_dynamicBody;

	for(int i = 0; i < numberOfPlanks;i++)
	{
		b2Body* plank;
		/*
		b2PolygonShape box2;
		box2.SetAsBox(size/2,5/2.0f);
		bodyDef.position.Set(thePosition.x+(size*(i+1)),thePosition.y);
		fixtureDef.shape = &box2;
		plank = world->CreateBody(&bodyDef);
		plank->CreateFixture( &fixtureDef );
		*/
		plank = BodyFactory::createBody(world,thePosition.x+((size+1)*(i+1)),thePosition.y,size,5,1,0.25f,true,true,myColIdent,3,1);
		b2WeldJointDef jointDef;
		jointDef.collideConnected = false;
		jointDef.dampingRatio = 1;
		if(i==0)
			jointDef.Initialize(Anchor,plank,Anchor->GetWorldCenter()); 
		else
			jointDef.Initialize(Planks.at(i-1),plank,Planks.at(i-1)->GetWorldCenter()); 
		b2WeldJoint* joint = (b2WeldJoint*)world->CreateJoint( &jointDef );

		Planks.push_back(plank);
	}
}


void Bridge::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{
	SDL_Rect stretchRect; 

	float rotation = (Anchor->GetAngle()*180.0/3.14159265);

	stretchRect.x = Anchor->GetPosition().x-(size/2)-offset.x;
	stretchRect.y = Anchor->GetPosition().y-(5/2.0f)-offset.y; 
	stretchRect.w = size; 
	stretchRect.h = 5;
	
	SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	for(int i = 0; i < Planks.size(); i++)
	{
		stretchRect.x = Planks.at(i)->GetPosition().x-(size/2)-offset.x;
		stretchRect.y =  Planks.at(i)->GetPosition().y-(5/2.0f)-offset.y; 
		stretchRect.w = size; 
		stretchRect.h = 5;
	
		rotation = ( Planks.at(i)->GetAngle()*180.0/3.14159265);
		SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
}

Bridge::Bridge(void)
	:BaseObject()
{
}


Bridge::~Bridge(void)
{
}
