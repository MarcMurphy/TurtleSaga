#include "Rope.h"

SDL_Point* Rope::rotatePoint = new SDL_Point();

Rope::Rope(b2World* world,b2Vec2 pos1,b2Vec2 size1,b2Vec2 pos2,b2Vec2 size2,float maxLength)
	:mPos1(pos1),mSize1(size1),mPos2(pos2),mSize2(size2),mMaxLength(maxLength)
{
	//b2BodyDef bodyDef;
	//b2FixtureDef fixtureDef;
	////fixtureDef.density = 1;
 // 
	////two boxes
	//b2PolygonShape squareShapeA;
	//squareShapeA.SetAsBox(mSize1.x/2,mSize1.y/2);
	//b2PolygonShape squareShapeB;
	//squareShapeB.SetAsBox(mSize2.x/2,mSize2.x/2);
 // 
	////large box a little to the left
	//bodyDef.position.Set(mPos1.x, mPos1.y);
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass=this;
	myColIdent->className="rope";
	//fixtureDef.shape = &squareShapeA;
	body1 = BodyFactory::BodyFactory().createBody(world,pos1.x,pos1.y,size1.x,size1.y,1,0,false,false,myColIdent,3,1);
		//world->CreateBody( &bodyDef );
	//body1->CreateFixture( &fixtureDef );
	//bodyDef.type = b2_dynamicBody;
	////smaller box a little to the right
	//bodyDef.position.Set( mPos2.x, mPos2.y);
	//fixtureDef.shape = &squareShapeB;
	body2 = BodyFactory::BodyFactory().createBody(world,pos2.x,pos2.y,size2.x,size2.y,1,0.25f,true,false,myColIdent,3,1);
		//world->CreateBody( &bodyDef );
	/*body2 = world->CreateBody( &bodyDef );
	body2->CreateFixture( &fixtureDef );*/

	b2RopeJointDef jd;
    jd.bodyA = body1;
    jd.bodyB = body2;
	b2Vec2 anchorA(mSize1.x/2,mSize1.y/2);
	b2Vec2 anchorB(mSize2.x/2,mSize2.y/2);
	jd.localAnchorA=anchorA;
	jd.localAnchorB=anchorB;
 
    // Max length of joint = current distance between bodies * sag
    float32 ropeLength = (body1->GetWorldPoint(anchorA) - body2->GetWorldPoint(anchorB)).Length();
	jd.maxLength = maxLength;
 
    // Create joint
    ropeJoint = (b2RopeJoint *)world->CreateJoint(&jd);
	
}


Rope::~Rope(void)
{
}

void Rope::render(SDL_Renderer* renderer, SDL_Texture* blockTex,SDL_Texture* ropeTex,b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//Draw rope	
	stretchRect.x = body1->GetWorldCenter().x-offset.x; 
	stretchRect.y = body1->GetWorldCenter().y-offset.y; 	
	stretchRect.w = 5; 
	stretchRect.h = b2Distance(body1->GetWorldCenter(),body2->GetWorldCenter());
	
	//render image
	float deltaY = body2->GetWorldCenter().y  - body1->GetWorldCenter().y; 
	float deltaX = body2->GetWorldCenter().x  - body1->GetWorldCenter().x; 


	float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.14;
	
	rotatePoint->x=body1->GetLocalCenter().x;
	rotatePoint->y=body1->GetLocalCenter().y;
	SDL_RenderCopyEx ( renderer, ropeTex, NULL, &stretchRect, angleInDegrees+270, rotatePoint, SDL_RendererFlip::SDL_FLIP_NONE );
	//draw anchor
	
	//to draw image at correct position
	stretchRect.x = body1->GetWorldCenter().x-(mSize1.x/2.0f)-offset.x;
	stretchRect.y = body1->GetWorldCenter().y-(mSize1.y/2.0f)-offset.y; 
	stretchRect.w = mSize1.x; 
	stretchRect.h = mSize1.y;
	//render image
	SDL_RenderCopy( renderer, blockTex, NULL, &stretchRect ); 

	//draw end of rope box
	stretchRect.x = body2->GetWorldCenter().x-(mSize2.x/2.0f)-offset.x;
	stretchRect.y = body2->GetWorldCenter().y-(mSize2.y/2.0f)-offset.y; 
	stretchRect.w = mSize2.x; 
	stretchRect.h = mSize2.y;
	//render image
	SDL_RenderCopy( renderer, blockTex, NULL, &stretchRect ); 


	
}