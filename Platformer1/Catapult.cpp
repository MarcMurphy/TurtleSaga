#include "Catapult.h"

Catapult::Catapult(float x, float y, float width, float height,  b2World* world): BaseObject()
{

	m_Dimentions.x = width;
	m_Dimentions.y = height;
	m_Position.x = x;
	m_Position.y = y;

	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="catapult";

//create base
	baseDimentions.x = width;
	baseDimentions.y = height / 2;
	basePosition.x = x;
	basePosition.y = y + height - baseDimentions.y;
	
	catapultBaseBody = BodyFactory::createBody(world, basePosition.x, basePosition.y,baseDimentions.x,baseDimentions.y,1.0,0.25,true,false,myColIdent,3,1);
	/*b2BodyDef standinBodyDef1;
	standinBodyDef1.position.Set(basePosition.x, basePosition.y);
	standinBodyDef1.type = b2_dynamicBody;
	catapultBaseBody = world->CreateBody(&standinBodyDef1);
	b2PolygonShape catapultBaseShape;
	catapultBaseShape.SetAsBox(baseDimentions.x/2, baseDimentions.y/2);
	catapultBaseBody->CreateFixture(&catapultBaseShape, 1.0f);*/

//create stop block
	stopBlockDimentions.x = width / 4;
	stopBlockDimentions.y = height;
	stopBlockPosition.x = x - width/2 + (stopBlockDimentions.x / 2);
	stopBlockPosition.y = y - baseDimentions.y;

	catapultStopBlockBody = BodyFactory::createBody(world, stopBlockPosition.x, stopBlockPosition.y, stopBlockDimentions.x,stopBlockDimentions.y,1,0.25,true,false,myColIdent,3,1);
	/*b2BodyDef standinBodyDef;
	standinBodyDef.position.Set(stopBlockPosition.x , stopBlockPosition.y);
	standinBodyDef.type = b2_dynamicBody;
	standinBodyDef.fixedRotation=true;
	catapultStopBlockBody = world->CreateBody(&standinBodyDef);
	b2PolygonShape catapultStopBlockShape;
	catapultStopBlockShape.SetAsBox(stopBlockDimentions.x/2, stopBlockDimentions.y/2);
	catapultStopBlockBody->CreateFixture(&catapultStopBlockShape, 1.0f);*/
	
//create anchor beam
	anchorBeamPosition.x = x;
	anchorBeamPosition.y = y;
	anchorBeamDimentions.x = (width / 8);
	anchorBeamDimentions.y = height;

	catapultAnchorBeamBody = BodyFactory::createBody(world, anchorBeamPosition.x, anchorBeamPosition.y, anchorBeamDimentions.x, anchorBeamDimentions.y,1.0,0.25,true,false,myColIdent,3,1);
	/*b2BodyDef standinBodyDef3;
	standinBodyDef3.position.Set(anchorBeamPosition.x, anchorBeamPosition.y);
	standinBodyDef3.type = b2_dynamicBody;
	standinBodyDef3.fixedRotation=true;
	catapultAnchorBeamBody = world->CreateBody(&standinBodyDef3);
	b2PolygonShape catapultAnchorBeamShape;
	catapultAnchorBeamShape.SetAsBox(anchorBeamDimentions.x/2, anchorBeamDimentions.y/2);
	catapultAnchorBeamBody->CreateFixture(&catapultAnchorBeamShape, 1.0f);*/

//create leaver
	leaverDimentions.x = width;
	leaverDimentions.y = height / 3;
	leaverPosition.x = x;
	leaverPosition.y = y - height + (leaverDimentions.y);

	catapultLeaverBody = BodyFactory::createBody(world, leaverPosition.x, leaverPosition.y, leaverDimentions.x, leaverDimentions.y,0.0002,0.25,true,true,myColIdent,3,1);
	/*b2BodyDef standinBodyDef2;
	standinBodyDef2.position.Set(leaverPosition.x, leaverPosition.y);
	standinBodyDef2.type = b2_dynamicBody;
	catapultLeaverBody = world->CreateBody(&standinBodyDef2);
	b2PolygonShape catapultLeaverShape;
	catapultLeaverShape.SetAsBox(leaverDimentions.x/2, leaverDimentions.y/2);
	catapultLeaverBody->CreateFixture(&catapultLeaverShape, 0.00001f);*/

//back wheel
	wheelRadius = width / 8;

	b2BodyDef standinBodyDef4;
	standinBodyDef4.position.Set(x - (width / 3), y + height);
	standinBodyDef4.type = b2_dynamicBody;
	standinBodyDef4.fixedRotation=false;
	catapultBackWheelBody = world->CreateBody(&standinBodyDef4);
	b2CircleShape catapultBackWheelShape;
	catapultBackWheelShape.m_radius = wheelRadius;
	catapultBackWheelBody->CreateFixture(&catapultBackWheelShape, 1.0f);

//front wheel
	b2BodyDef standinBodyDef5;
	standinBodyDef5.position.Set(x + (width / 3), y + height);
	standinBodyDef5.type = b2_dynamicBody;
	standinBodyDef5.fixedRotation=false;
	catapultFrontWheelBody = world->CreateBody(&standinBodyDef5);
	b2CircleShape catapultFrontWheelShape;
	catapultFrontWheelShape.m_radius = wheelRadius;
	catapultFrontWheelBody->CreateFixture(&catapultFrontWheelShape, 1.0f);

/////////////////
//create joints//
/////////////////

	// leaver -> anchor
	b2RevoluteJointDef revoluteJointDef;
	b2Vec2 ancorPoint = catapultLeaverBody->GetWorldCenter();
	
	revoluteJointDef.Initialize(catapultAnchorBeamBody, catapultLeaverBody, ancorPoint);
	revoluteJointDef.collideConnected = true;

	world->CreateJoint(&revoluteJointDef);

	// base -> anchor beam
	b2DistanceJointDef jointDef;
	jointDef.Initialize(catapultBaseBody, catapultAnchorBeamBody, catapultBaseBody->GetPosition(), catapultAnchorBeamBody->GetPosition());
	jointDef.collideConnected = true;
	world->CreateJoint(&jointDef);

	// base -> stop block
	b2DistanceJointDef jointDef2;
	jointDef2.Initialize(catapultBaseBody, catapultStopBlockBody, catapultBaseBody->GetPosition(), catapultStopBlockBody->GetPosition());
	jointDef2.collideConnected = true;
	world->CreateJoint(&jointDef2);

	// stop block -> anchor beam
	b2DistanceJointDef jointDef3;
	jointDef3.Initialize(catapultStopBlockBody, catapultAnchorBeamBody, catapultStopBlockBody->GetPosition(), catapultAnchorBeamBody->GetPosition());
	jointDef3.collideConnected = true;
	world->CreateJoint(&jointDef3);

	//back wheel -> base
	b2RevoluteJointDef revoluteJointDef2;
	b2Vec2 ancorPoint2 = catapultBackWheelBody->GetWorldCenter();
	
	revoluteJointDef2.Initialize(catapultBackWheelBody, catapultBaseBody, ancorPoint2);
	revoluteJointDef2.collideConnected = false;

	world->CreateJoint(&revoluteJointDef2);

	//front wheel -> base
	b2RevoluteJointDef revoluteJointDef3;
	b2Vec2 ancorPoint3 = catapultFrontWheelBody->GetWorldCenter();
	
	revoluteJointDef3.Initialize(catapultFrontWheelBody, catapultBaseBody, ancorPoint3);
	revoluteJointDef3.collideConnected = false;

	world->CreateJoint(&revoluteJointDef3);
}

Catapult::~Catapult(void)
{
}

Catapult* Catapult::createCatapult(float x, float y, float width, float height,  b2World* world){
	if(Catapult::m_Catapult == NULL){
		Catapult::m_Catapult = new Catapult(x, y, width, height, world);
	}
	return Catapult::m_Catapult;
}
	
b2Vec2 Catapult::getPosition(){
	return m_Position;
}

void Catapult::update(){

}

void Catapult::render(SDL_Renderer* renderer, SDL_Texture* textureBase,SDL_Texture* catapultBlock,SDL_Texture* catapultWheel,SDL_Texture* catapultBeam,SDL_Texture* catapultArm, b2Vec2 offset)
{
	SDL_Rect stretchRect; 

	//draw base
	stretchRect.x = catapultBaseBody->GetPosition().x - offset.x - (baseDimentions.x/2);
	stretchRect.y = catapultBaseBody->GetPosition().y - offset.y - (baseDimentions.y/2); 
	stretchRect.w = baseDimentions.x;
	stretchRect.h = baseDimentions.y;
	SDL_RenderCopy( renderer, textureBase, NULL, &stretchRect );
	
	//draw anchor beam
	stretchRect.x = catapultAnchorBeamBody->GetPosition().x - offset.x - (anchorBeamDimentions.x/2);
	stretchRect.y = catapultAnchorBeamBody->GetPosition().y - offset.y - (anchorBeamDimentions.y/2); 
	stretchRect.w = anchorBeamDimentions.x;
	stretchRect.h = anchorBeamDimentions.y;
	SDL_RenderCopy( renderer, catapultBeam, NULL, &stretchRect );

	//draw stop block
	stretchRect.x = catapultStopBlockBody->GetPosition().x - offset.x - (stopBlockDimentions.x/2);
	stretchRect.y = catapultStopBlockBody->GetPosition().y - offset.y - (stopBlockDimentions.y/2); 
	stretchRect.w = stopBlockDimentions.x;
	stretchRect.h = stopBlockDimentions.y;
	SDL_RenderCopy( renderer, catapultBlock, NULL, &stretchRect );

	//draw leaver
	double rotation = (catapultLeaverBody->GetAngle()*180.0/3.14159265);
	stretchRect.x = catapultLeaverBody->GetPosition().x - offset.x -(leaverDimentions.x/2);
	stretchRect.y = catapultLeaverBody->GetPosition().y - offset.y -(leaverDimentions.y/2);
	stretchRect.w = leaverDimentions.x ;
	stretchRect.h = leaverDimentions.y ;
	
	SDL_RenderCopyEx( renderer, catapultArm, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

	//draw wheels
	double rotation2 = (catapultBackWheelBody->GetAngle()*180.0/3.14159265);
	stretchRect.x = catapultBackWheelBody->GetPosition().x - offset.x - (wheelRadius);
	stretchRect.y = catapultBackWheelBody->GetPosition().y - offset.y - (wheelRadius); 
	stretchRect.w = wheelRadius * 2;
	stretchRect.h = wheelRadius * 2;
	SDL_RenderCopyEx( renderer, catapultWheel, NULL, &stretchRect, rotation2, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

	stretchRect.x = catapultFrontWheelBody->GetPosition().x - offset.x - (wheelRadius);
	stretchRect.y = catapultFrontWheelBody->GetPosition().y - offset.y - (wheelRadius); 
	SDL_RenderCopyEx( renderer, catapultWheel, NULL, &stretchRect, rotation2, NULL, SDL_RendererFlip::SDL_FLIP_NONE );


}