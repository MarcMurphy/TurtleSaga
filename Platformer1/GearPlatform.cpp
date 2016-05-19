#include "GearPlatform.h"

GearPlatform* GearPlatform::CreateGear(b2World* world,b2Vec2 posCrank, b2Vec2 sizeCrank, b2Vec2 posPlatform, b2Vec2 sizePlatform, b2Vec2 direction)
{
	return new GearPlatform(world,posCrank,sizeCrank,posPlatform,sizePlatform,direction);
}

GearPlatform::GearPlatform(b2World* world,b2Vec2 posCrank, b2Vec2 sizeCrank, b2Vec2 posPlatform, b2Vec2 sizePlatform, b2Vec2 direction)
	: mSizeCrank(sizeCrank),mSizePlatform(sizePlatform){
	
	/*
	/setup platform properties
	*/
	
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass=this;
	myColIdent->className="gear";
	myColIdentPlat = new CollisionIdentifier();
	myColIdentPlat->baseClass=this;
	myColIdentPlat->className="gearPlat";
	
	body1 = BodyFactory::BodyFactory().createBody(world,posPlatform.x,posPlatform.y,sizePlatform.x,sizePlatform.y,2,0.25f,true,false,myColIdentPlat,3,1);
	
	body2 = BodyFactory::BodyFactory().createBody(world,posCrank.x,posCrank.y,sizeCrank.x,sizeCrank.y,2,0.25f,true,true,myColIdent,3,1);


	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//
	//bodyDef.fixedRotation = false;
	//b2FixtureDef fixtureDef;
	//fixtureDef.density = 0.01f;
	//fixtureDef.friction = 0;
	///*
	//setup platform body
	//*/
	//b2PolygonShape platform;
	//platform.SetAsBox(mSizePlatform.x/2.0f, mSizePlatform.y/2.0f);
	//bodyDef.position.Set(posPlatform.x,posPlatform.y);
	//fixtureDef.shape = &platform;
	//fixtureDef.density = 2.0f;
	//
	//body1 = world->CreateBody(&bodyDef);
	//body1->CreateFixture( &fixtureDef );

	///*
	//setup crank properties
	//*/	
	//bodyDef.type = b2_dynamicBody;
	//platform.SetAsBox(mSizeCrank.x/2.0f, mSizeCrank.y/2.0f);
	//bodyDef.position.Set(posCrank.x,posCrank.y);
	//fixtureDef.shape = &platform;
	//fixtureDef.density = 2.0f;
	//body2 = world->CreateBody(&bodyDef);
	//body2->CreateFixture( &fixtureDef );
	/*
	setup joints
	*/	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);
	groundBody = world->CreateBody(&groundBodyDef);
	

	b2PrismaticJointDef jointDef;
	jointDef.Initialize(groundBody,body1, body1->GetWorldCenter(),direction);
	translationJoint = (b2PrismaticJoint*)world->CreateJoint( &jointDef);

	b2RevoluteJointDef revjointDef;
	revjointDef.Initialize(groundBody,body2,body2->GetWorldCenter());
	revjointDef.collideConnected = false;

	//revjointDef.Initialize(body1,body2,body2->GetWorldCenter());
	rotationJoint = (b2RevoluteJoint*)world->CreateJoint( &revjointDef );
	//setup joint stuff
	
	b2GearJointDef gearJointDef;
	gearJointDef.bodyA = body1;
	gearJointDef.bodyB = body2;	
	gearJointDef.joint1 = translationJoint;
	gearJointDef.joint2 = rotationJoint;
	
	gearJointDef.ratio = 5;

	gearJoint = (b2GearJoint*)world->CreateJoint( &gearJointDef );
}


GearPlatform::~GearPlatform(void)
{
}
void GearPlatform::resetVelocities(){
	body2->SetAngularVelocity(0);
	body2->SetLinearVelocity(b2Vec2(0,0));
}
void GearPlatform::rotateClockwise(){
	body2->SetAngularVelocity(0.5);
	//body1->SetLinearVelocity(b2Vec2(0,0.5));
	
}
void GearPlatform::rotateCounterClockwise(){
	body2->SetAngularVelocity(-0.5);
	//body1->SetLinearVelocity(b2Vec2(0,-2));
}
void GearPlatform::render(SDL_Renderer* renderer, SDL_Texture* texture, b2Vec2 offset)
{
	
	SDL_Rect stretchRect; 

	//render platform
	stretchRect.x = body2->GetPosition().x-(mSizeCrank.x/2.0f)-offset.x; 
	stretchRect.y = body2->GetPosition().y-(mSizeCrank.y/2.0f)-offset.y; 
	
	stretchRect.w = mSizeCrank.x; 
	stretchRect.h = mSizeCrank.y;
	//render image

	SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, body2->GetAngle()*180/3.14, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

	//render crank
	stretchRect.x = body1->GetPosition().x-(mSizePlatform.x/2.0f)-offset.x; 
	stretchRect.y = body1->GetPosition().y-(mSizePlatform.y/2.0f)-offset.y;  
	stretchRect.w = mSizePlatform.x; 
	stretchRect.h = mSizePlatform.y;
	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 

}
