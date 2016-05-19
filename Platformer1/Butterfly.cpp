#include "Butterfly.h"


static Butterfly* CreateButterfly(float x,  float y, Player* player,b2World* world){
	return new Butterfly(x,y,player,world);
}

Butterfly::Butterfly(float x, float y, Player* p,b2World* world) 
	: player(p), mWidth(64),mHeight(128),mTimeBetweenShots(10000),mWorld(world), numFrames(2),frame(1),animationTimer(0),health(200)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass=this;
	myColIdent->className="butterfly";
	Body = BodyFactory::createBody(world,x,y,mWidth,mHeight,1,1,false,false,myColIdent,5,2);
	//b2BodyDef BodyDef;
	//
	//BodyDef.position.Set(x,  y);
	//Body = world->CreateBody(&BodyDef);
	//b2PolygonShape Box;
	////sets box with position centered and given width and height in each direction(hence /2)
	//Box.SetAsBox(mWidth/2.0f, mHeight/2.0f);
	//
	//Body->CreateFixture(&Box, 0.0f);
}


Butterfly::~Butterfly(void)
{
}

void Butterfly::Update(float deltaTime){
	mTotalTime+=deltaTime;
	animationTimer+=deltaTime;
	if(mTotalTime>=mTimeBetweenShots){
		ObjectManager::getManager()->trees.push_back(new Tree(0.5,Body->GetWorldCenter()+b2Vec2(0,mHeight/2),5,ObjectManager::getManager()->player,mWorld,b2Vec2(-100000,-100000)));
		SoundManager::getSoundManager()->playTreeLaunch();
		mTotalTime=0;
	}
	if(animationTimer>=300){
		frame++;
		animationTimer=0;
	}
	
}

//Tree* Butterfly::CreateTree(float x, float y, float strength){
	//return new Tree(x,y,strength);
//}

void Butterfly::render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* texture2, SDL_Texture* texture3, b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//to draw image at correct position
	stretchRect.x = Body->GetPosition().x-(mWidth/2.0f)-offset.x; 
	stretchRect.y = Body->GetPosition().y-(mHeight/2.0f)-offset.y; 
	stretchRect.w = mWidth; 
	stretchRect.h = mHeight;
	//render image
	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 

	
	//to draw image at correct position
	stretchRect.x = Body->GetPosition().x-(mWidth*3.0f/4.0f)-offset.x; 
	stretchRect.y = Body->GetPosition().y-(mHeight/2.0f)-offset.y- 25; 
	stretchRect.w = 2*mWidth*(health/200.0f); 
	stretchRect.h = 10;
	//render image
	SDL_RenderCopy( renderer, texture3, NULL, &stretchRect ); 


	//to draw image at correct position
	stretchRect.x = Body->GetPosition().x-(mWidth*5.0f)-offset.x; 
	stretchRect.y = Body->GetPosition().y-(mHeight/2.0f)-offset.y - 100; 
	stretchRect.w = 10*mWidth; 
	stretchRect.h = 200;
	//render image
	SDL_RenderCopy( renderer, texture2, NULL, &stretchRect ); 

	
}
