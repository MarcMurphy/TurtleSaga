#include "Elevator.h"



SDL_Point* Elevator::rotatePoint = new SDL_Point();
//
Elevator::Elevator(b2World* world, float body1X,float body1Y, float body1Width,float body1Height, float body1Density,
				   float body2X,float body2Y, float body2Width,float body2Height,float body2Density,
				   float anchor1X,float anchor1Y,float anchor2X,float anchor2Y)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="elevator";

	body1 = BodyFactory::createBody(world,body1X,body1Y,body1Width,body1Height,body1Density,0.25f,true,false,myColIdent,3,1);
	body2 = BodyFactory::createBody(world,body2X,body2Y,body2Width,body2Height,body2Density,0.25f,true,false,myColIdent,3,1);
	size1 = b2Vec2(body1Width,body1Height);
	size2 = b2Vec2(body2Width,body2Height);


	//b2BodyDef BodyDef1;
	//BodyDef1.type = b2_dynamicBody;
	//BodyDef1.position.Set(body1X,  body1Y);
	//BodyDef1.fixedRotation = true;
	//BodyDef1.userData = myColIdent;
	//body1 = world->CreateBody(&BodyDef1);
	//b2PolygonShape Box1;
	////sets box with position centered and given width and height in each direction(hence /2)
	//Box1.SetAsBox(body1Width/2.0f, body1Height/2.0f);
	//b2FixtureDef fixtureDef1;
	//fixtureDef1.shape = &Box1;
	//fixtureDef1.density = body1Density;
	//fixtureDef1.friction = 0.250f;
	//body1->CreateFixture(&fixtureDef1);

	//b2BodyDef BodyDef2;
	//BodyDef2.type = b2_dynamicBody;
	//BodyDef2.position.Set(body2X,  body2Y);
	//BodyDef2.fixedRotation = true;
	//BodyDef2.userData = myColIdent;
	//body2 = world->CreateBody(&BodyDef2);
	//b2PolygonShape Box2;
	////sets box with position centered and given width and height in each direction(hence /2)
	//Box2.SetAsBox(body2Width/2.0f, body2Height/2.0f);
	//b2FixtureDef fixtureDef2;
	//fixtureDef2.shape = &Box2;
	//fixtureDef2.density = body2Density;
	//fixtureDef2.friction = 0.250f;
	//body2->CreateFixture(&fixtureDef2);



	b2PulleyJointDef jointDef;
	anchor1 = b2Vec2(anchor1X,anchor1Y);
	anchor2 = b2Vec2(anchor2X,anchor2Y);
	jointDef.Initialize(body1,body2,anchor1 ,anchor2 ,body1->GetWorldCenter(),body2->GetWorldCenter(),1);

	b2PulleyJoint* joint = (b2PulleyJoint*)world->CreateJoint( &jointDef );
}


Elevator::~Elevator(void)
{
}



void Elevator::render(SDL_Renderer* renderer, SDL_Texture* texture,SDL_Texture* texture2,SDL_Texture* texture3,SDL_Texture* texture4,b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//Draw rope	
	stretchRect.x = anchor1.x-1-offset.x; 
	stretchRect.y = anchor1.y-31-offset.y; 	
	stretchRect.w = 2; 
	stretchRect.h = b2Distance(anchor1,b2Vec2(body1->GetWorldCenter().x,body1->GetWorldCenter().y-(size1.y/2.0f)));
	
	//render image
	float deltaY = (body1->GetWorldCenter().y-31-(size1.y/2.0f))  - (anchor1.y-31); 
	float deltaX = body1->GetWorldCenter().x  - anchor1.x; 


	float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.14;
	
	rotatePoint->x=body1->GetLocalCenter().x;
	rotatePoint->y=body1->GetLocalCenter().y;
	SDL_RenderCopyEx ( renderer, texture4, NULL, &stretchRect, angleInDegrees+270, rotatePoint, SDL_RendererFlip::SDL_FLIP_NONE );



	

	//Draw rope	2
	stretchRect.x = anchor1.x-1-offset.x; 
	stretchRect.y = anchor1.y-31-offset.y; 	
	stretchRect.w = 2; 
	stretchRect.h = b2Distance(anchor1,anchor2);
	
	//render image
	 deltaY = (anchor2.y)  - (anchor1.y); 
	 deltaX = anchor2.x  - anchor1.x; 


	 angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.14;
	
	 rotatePoint = new SDL_Point();
	rotatePoint->x=0;
	rotatePoint->y=0;
	SDL_RenderCopyEx ( renderer, texture4, NULL, &stretchRect, angleInDegrees+270, rotatePoint, SDL_RendererFlip::SDL_FLIP_NONE );



	

	//Draw rope	3
	stretchRect.x = anchor2.x-1-offset.x; 
	stretchRect.y = anchor2.y-31-offset.y; 	
	stretchRect.w = 2; 
	stretchRect.h = b2Distance(anchor2,b2Vec2(body2->GetWorldCenter().x,body2->GetWorldCenter().y-(size2.y/2.0f)));
	
	//render image
	 deltaY = (body2->GetWorldCenter().y-31-(size2.y/2.0f))  - (anchor2.y-31); 
	 deltaX = body2->GetWorldCenter().x  - anchor2.x; 


	 angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.14;
	
	 rotatePoint = new SDL_Point();
	rotatePoint->x=body2->GetLocalCenter().x;
	rotatePoint->y=body2->GetLocalCenter().y;
	SDL_RenderCopyEx ( renderer, texture4, NULL, &stretchRect, angleInDegrees+270, rotatePoint, SDL_RendererFlip::SDL_FLIP_NONE );




	//to draw image at correct position
	stretchRect.x = body1->GetPosition().x-(size1.x/2.0f)-offset.x;
	stretchRect.y = body1->GetPosition().y-(size1.y/2.0f)-offset.y; 
	stretchRect.w = size1.x; 
	stretchRect.h = size1.y;
	//render image
	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 

	
	stretchRect.x = body1->GetPosition().x-(size1.x/2.0f)-offset.x;
	stretchRect.y = body1->GetPosition().y-(size1.y/2.0f)-31-offset.y; 
	stretchRect.w = size1.x; 
	stretchRect.h = 32;
	//render image
	SDL_RenderCopy( renderer, texture3, NULL, &stretchRect ); 

	stretchRect.x = body2->GetPosition().x-(size2.x/2.0f)-offset.x;
	stretchRect.y = body2->GetPosition().y-(size2.y/2.0f)-offset.y; 
	stretchRect.w = size2.x; 
	stretchRect.h = size2.y;
	//render image
	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 

	stretchRect.x = body2->GetPosition().x-(size2.x/2.0f)-offset.x;
	stretchRect.y = body2->GetPosition().y-(size2.y/2.0f)-31-offset.y; 
	stretchRect.w = size2.x; 
	stretchRect.h = 32;
	//render image
	SDL_RenderCopy( renderer, texture3, NULL, &stretchRect ); 

	
	stretchRect.x = anchor1.x-(20/2.0f)-offset.x;
	stretchRect.y = anchor1.y-(20/2.0f)-31-offset.y; 
	stretchRect.w = 20; 
	stretchRect.h = 20;
	//render image
	SDL_RenderCopy( renderer, texture2, NULL, &stretchRect ); 

	
	stretchRect.x = anchor2.x-(20/2.0f)-offset.x;
	stretchRect.y = anchor2.y-(20/2.0f)-31-offset.y; 
	stretchRect.w = 20; 
	stretchRect.h = 20;
	//render image
	SDL_RenderCopy( renderer, texture2, NULL, &stretchRect );
	
	


	
}