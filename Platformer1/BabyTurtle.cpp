#include "BabyTurtle.h"


BabyTurtle::BabyTurtle(float x,float y, b2World* world):mWidth(24),mHeight(32),dead(false)
{

	
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="baby";
	walk[0] = 0;
	walk[1] = 1;
	walk[2] = 2;
	walk[3] = 1;
	imgNum = 0;
	body = BodyFactory::createBody(world,x,y,mWidth,mHeight,0.05,1,true,false,myColIdent,2,1);
	

}


BabyTurtle::~BabyTurtle(void)
{
}


void BabyTurtle::Update(b2Body* followBody,b2Body* enemyBody, float deltaTime)
{
	animationTime+=deltaTime;
	b2Vec2 enemyDist =  enemyBody->GetPosition()-followBody->GetPosition();
	if(((enemyDist.x)*(enemyDist.x))+((enemyDist.y)*(enemyDist.y))<25000)
	{
		b2Vec2 dif = enemyBody->GetPosition()-body->GetPosition();
		if(((dif.x)*(dif.x))+((dif.y)*(dif.y))>5000)
		{
			dif.x *= 5;
			dif.y *= 5;
			body->ApplyLinearImpulse(dif,b2Vec2(0,0),true);
		}
	}
	else
	{
		b2Vec2 dif = followBody->GetPosition()-body->GetPosition();
		if(((dif.x)*(dif.x))+((dif.y)*(dif.y))>5000)
		{
			dif.x *= 5;
			dif.y *= 5;
			body->ApplyLinearImpulse(dif,b2Vec2(0,0),true);
		}
	}
}


void BabyTurtle::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{


	SDL_Rect stretchRect; 
	//to draw image at correct position
	stretchRect.x = body->GetPosition().x-(mWidth/2.0f)-offset.x; 
	stretchRect.y = body->GetPosition().y-(mHeight/2.0f)-offset.y; 
	stretchRect.w = mWidth; 
	stretchRect.h = mHeight;
	//render image
	//SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 
	if(animationTime>=90)
	{
		imgNum=(imgNum+1)%4;
		animationTime=0;
	}
	if(body->GetLinearVelocity().x>0)
	{
		SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect,0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}
	else
	{
		SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect,0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
	
	
}