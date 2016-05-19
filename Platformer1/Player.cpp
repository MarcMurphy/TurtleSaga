#include "Player.h"


Player* Player::CreatePlayer(float x,float y, b2World* world)
{
	return new Player( x, y, world);
}

Player::Player(float x, float y, b2World* world): mSpeed(1),mWidth(48),mHeight(64),isBlocking(false),facingRight(true),dead(false)
{

	
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="player";
	walk[0] = 0;
	walk[1] = 1;
	walk[2] = 2;
	walk[3] = 1;
	imgNum = 0;
	Body = BodyFactory::createBody(world,x,y,mWidth,mHeight,1,2,true,false,myColIdent,3,1|4);
	//b2BodyDef BodyDef;
	//BodyDef.type = b2_dynamicBody;
	//BodyDef.position.Set(x,  y);
	//BodyDef.userData = myColIdent;
	//BodyDef.fixedRotation = true;
	//Body = world->CreateBody(&BodyDef);
	//b2PolygonShape Box;
	////sets box with position centered and given width and height in each direction(hence /2)
	//Box.SetAsBox(mWidth/2.0f, mHeight/2.0f);
	//
	//b2FixtureDef fixtureDef;

	//fixtureDef.shape = &Box;
	//fixtureDef.density = 0.250f;
	//fixtureDef.friction = 1.0f;
	//Body->CreateFixture(&fixtureDef);	

	moveForceLevel =4000;
	jumpForceLevel = 400000;

}


Player::~Player(void)
{
}

void Player::MoveLeft(){
	this->Body->ApplyForceToCenter(b2Vec2(-moveForceLevel,0),true);
	facingRight=false;
}
void Player::MoveRight(){
	this->Body->ApplyForceToCenter(b2Vec2(moveForceLevel,0),true);
	facingRight=true;
}
void Player::Jump()
{
	if(!inAir)
	{
		if(jumpCharge<-jumpForceLevel)
		{
			jumpCharge=-jumpForceLevel;
		}
		this->Body->ApplyForceToCenter(b2Vec2(0,-50000+jumpCharge),true);
		//SoundManager::getSoundManager()->playJump();
		//this->Body->SetLinearDamping(0);
		//this->Body->SetLinearVelocity(b2Vec2(Body->GetLinearVelocity().x,-1000000000));
	}
}
void Player::Update(float deltaTime){
	animationTime+=deltaTime;
	isBlocking = false;
	if(KeyHandler::getKeys()->Key_Space)
	{
		Body->SetTransform(Body->GetPosition(),1.57079633f);
		isBlocking=true;
		jumpCharge=0;
	}
	else
	{
		Body->SetTransform(Body->GetPosition(),0);
		isBlocking=false;
		if(KeyHandler::getKeys()->Key_Up)
		{
			jumpCharge-=(jumpForceLevel+jumpCharge)/50;
		}
		else if(jumpCharge!=0)
		{
			Jump();
			jumpCharge=0;
			inAir = true;
		}
		if(KeyHandler::getKeys()->Key_Left)
			this->MoveLeft();
		if(KeyHandler::getKeys()->Key_Right)
			MoveRight();
	}


}

void Player::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//to draw image at correct position
	if(isBlocking)
	{
		stretchRect.x = Body->GetPosition().x-(mHeight/2.0f)-offset.x; 
		stretchRect.y = Body->GetPosition().y-(mWidth/2.0f)-offset.y; 
		stretchRect.w = mHeight;
		stretchRect.h = mWidth;
	}
	else
	{
		stretchRect.x = Body->GetPosition().x-(mWidth/2.0f)-offset.x; 
		stretchRect.y = Body->GetPosition().y-(mHeight/2.0f)-offset.y; 
		stretchRect.w = mWidth; 
		stretchRect.h = mHeight;
	}
	//render image
	//SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 
	if(KeyHandler::getKeys()->Key_Left||KeyHandler::getKeys()->Key_Right)
	{
		if(animationTime>=90)
		{
			imgNum=(imgNum+1)%4;
			animationTime=0;
		}
	}
	if(facingRight)
	{
		SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect,0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
	}
	else
	{
		SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect,0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
	
}
