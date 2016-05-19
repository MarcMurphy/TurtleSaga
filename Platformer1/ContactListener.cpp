
#include "ContactListener.h"

ContactListener* ContactListener::me;

ContactListener* ContactListener::createListener()
{
	if(me == NULL)
	{
		me = new ContactListener();
	}
	return me;
}

ContactListener::ContactListener(void)
{
}


ContactListener::~ContactListener(void)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	bool looking = true;
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();
	CollisionIdentifier* body1Ident = ((CollisionIdentifier*)body1->GetUserData());
	CollisionIdentifier* body2Ident = ((CollisionIdentifier*)body2->GetUserData());
	Player* player=NULL;
	Platform* platform=NULL;
	Elevator* elevator=NULL;
	Tree* tree = NULL;
	Nest* nest = NULL;
	GearPlatform* gear = NULL;
	GearPlatform* gearPlat = NULL;
	Bridge* bridge = NULL;
	PrismaticBox* prisBox = NULL;
	PushableBlock* pushBlock = NULL;
	Rope* rope = NULL;
	Butterfly* butterfly=NULL;
	BabyTurtle* baby = NULL;
	Catapult* catapult = NULL;

	if(body1Ident !=  NULL)
	{
		if(body1Ident->className == "player")
		{
			player = (Player*)body1Ident->baseClass;
		}
		if(body1Ident->className == "tree")
		{
			tree = (Tree*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "platform")
		{
			platform = (Platform*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "elevator")
		{
			elevator = (Elevator*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "nest")
		{
			nest = (Nest*)body1Ident->baseClass;
		}
		
		else if(body1Ident->className == "gearPlat")
		{
			gearPlat = (GearPlatform*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "gear")
		{
			gear = (GearPlatform*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "bridge")
		{
			bridge = (Bridge*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "prismaticBox")
		{
			prisBox = (PrismaticBox*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "pushBlock")
		{
			pushBlock = (PushableBlock*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "rope")
		{
			rope = (Rope*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "butterfly")
		{
			butterfly = (Butterfly*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "baby")
		{
			baby = (BabyTurtle*)body1Ident->baseClass;
		}
		else if(body1Ident->className == "catapult")
		{
			catapult = (Catapult*)body1Ident->baseClass;
		}
	}
	if(body2Ident !=  NULL)
	{
		if(body2Ident->className == "player")
		{
			player = (Player*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "platform")
		{
			platform = (Platform*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "elevator")
		{
			elevator = (Elevator*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "tree")
		{
			tree = (Tree*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "nest")
		{
			nest = (Nest*)body2Ident->baseClass;
		}
		
		else if(body2Ident->className == "gearPlat")
		{
			gearPlat = (GearPlatform*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "gear")
		{
			gear = (GearPlatform*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "bridge")
		{
			bridge = (Bridge*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "prismaticBox")
		{
			prisBox = (PrismaticBox*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "pushBlock")
		{
			pushBlock = (PushableBlock*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "rope")
		{
			rope = (Rope*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "butterfly")
		{
			butterfly = (Butterfly*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "baby")
		{
			baby = (BabyTurtle*)body2Ident->baseClass;
		}
		else if(body2Ident->className == "catapult")
		{
			catapult = (Catapult*)body2Ident->baseClass;
		}

	}

	if(player !=NULL)
	{
		if(platform != NULL)
		{
			player->inAir=false;
		}
		else if(elevator != NULL)
		{
			player->inAir=false;
		}

		if(tree!=NULL)
		{
			tree->mDestroyJoints = true;
			b2Vec2 dif = player->Body->GetPosition()-tree->mTreeMidBody->GetPosition();
			{
				player->Body->ApplyLinearImpulse(b2Vec2(dif.x*100000,dif.y*10000),player->Body->GetPosition(),true);
				dif.x *= -500;
				dif.y *= -500;
				tree->mTreeMidBody->ApplyLinearImpulse(dif,tree->mTreeMidBody->GetPosition(),true);
				tree->mTreeTopBody->ApplyLinearImpulse(dif,tree->mTreeTopBody->GetPosition(),true);
				tree->mTreeBotBody->ApplyLinearImpulse(dif,tree->mTreeBotBody->GetPosition(),true);
			}
			if(player->isBlocking==false)
			{
				if(ObjectManager::getManager()->babyTurtles.size()>0)
				{
					ObjectManager::getManager()->babyTurtles.at(ObjectManager::getManager()->babyTurtles.size()-1)->dead=true;
				}
				else
				{
					ObjectManager::getManager()->player->dead=true;
				}
			}
		}
		if(nest!=NULL)
		{
			nest->mHatchEgg = true;
		}
		if(gear!=NULL)
		{
			player->inAir=false;
			gear->rotateCounterClockwise();
		}
		if(gearPlat!=NULL)
		{
			player->inAir=false;
		}
		if(bridge!=NULL)
		{
			player->inAir=false;
		}
		if(prisBox!=NULL)
		{
			player->inAir=false;
		}
		if(pushBlock!=NULL)
		{
			player->inAir=false;
		}
		if(rope!=NULL)
		{
			player->inAir=false;
		}
		if(catapult!=NULL)
		{
			player->inAir=false;
		}
		if(butterfly!=NULL)
		{
			butterfly->health-=10;
		}

	}
	else
	{
		if(baby!=NULL)
		{
			if(butterfly!=NULL)
			{
				b2Vec2 dif = baby->body->GetPosition()-butterfly->Body->GetPosition();
				{
					baby->body->ApplyLinearImpulse(b2Vec2(dif.x*500000000,dif.y*50000000),baby->body->GetPosition(),true);
					butterfly->health-=1;
				}
			}
		}
	}

}
void ContactListener::EndContact(b2Contact* contact)
{

}
