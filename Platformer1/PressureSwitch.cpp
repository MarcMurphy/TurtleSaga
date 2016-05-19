#include "pressureSwitch.h"

PressureSwitch::PressureSwitch(b2World* world,b2Vec2 thePosition)
{
	setPosition(thePosition);

	///////////////////////////////////
	b2CircleShape circleShape;
	circleShape.m_radius = 8;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;
	//fixtureDef.filter.categoryBits = RADAR_SENSOR;
	//fixtureDef.filter.maskBits = ENEMY_AIRCRAFT;//radar only collides with aircraft
	//ship->m_body->CreateFixture(&fixtureDef);
	//////////////////////////////////
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	fixtureDef.density = 0.01f;
	fixtureDef.friction = 0;

	b2PolygonShape box1;
	box1.SetAsBox(20/2.0f, 20/2.0f);
	bodyDef.position.Set(thePosition.x,thePosition.y);
	fixtureDef.shape = &box1;
	boxSwitch = world->CreateBody(&bodyDef);
	boxSwitch->CreateFixture( &fixtureDef );
}

void PressureSwitch::setPosition(b2Vec2 thePosition)
{
	position = thePosition;
}

void PressureSwitch::setActive(bool isActive)
{
	active = isActive;
}

void PressureSwitch::Update()
{
	
}

void PressureSwitch::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect stretchRect; 

	stretchRect.x = boxSwitch->GetPosition().x-(20/2.0f);
	stretchRect.y = boxSwitch->GetPosition().y-(20/2.0f); 
	stretchRect.w = 20; 
	stretchRect.h = 20;

	SDL_RenderCopy( renderer, texture, NULL, &stretchRect ); 
}

PressureSwitch::PressureSwitch(void)
	:BaseObject()
{
}


PressureSwitch::~PressureSwitch(void)
{
}
