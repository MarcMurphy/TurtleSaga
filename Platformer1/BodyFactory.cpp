#include "BodyFactory.h"


BodyFactory::BodyFactory(void)
{
}


BodyFactory::~BodyFactory(void)
{
}


b2Body* BodyFactory::createBody(b2World* world, float x, float y,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent,
								int16 categoryBits, int16 maskBits)
{
	b2BodyDef BodyDef;
	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	BodyDef.position.Set(x,  y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(width/2.0f, height/2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = maskBits;
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);
	return body;
}