#include "Game.h"

bool Game::victory;
Game::Game(){}

Game::Game(SDL_Renderer* renderer,b2World* world)
{
	mRenderer = renderer;
	mWorld = world;
	TotalTimeElapsed = 0;
	victory = false;
	LevelBuilder();
	
}

void Game::LevelBuilder()
{
	
	for(int i = 0; i < ObjectManager::getManager()->catapults.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultAnchorBeamBody);
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultBackWheelBody);
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultBaseBody);
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultFrontWheelBody);
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultLeaverBody);
		mWorld->DestroyBody(ObjectManager::getManager()->catapults.at(i)->catapultStopBlockBody);
	}
	ObjectManager::getManager()->catapults.erase(ObjectManager::getManager()->catapults.begin(),ObjectManager::getManager()->catapults.end());

	
	for(int i = 0; i < ObjectManager::getManager()->platforms.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->platforms.at(i)->Body);
	}
	ObjectManager::getManager()->platforms.erase(ObjectManager::getManager()->platforms.begin(),ObjectManager::getManager()->platforms.end());
	
	/*for(int i = 0; i < ObjectManager::getManager()->trees.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->trees.at(i)->mBody);
	}
	ObjectManager::getManager()->trees.erase(ObjectManager::getManager()->trees.begin(),ObjectManager::getManager()->trees.end());
	*/
	for(int i = 0; i < ObjectManager::getManager()->elevators.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->elevators.at(i)->body1);
		mWorld->DestroyBody(ObjectManager::getManager()->elevators.at(i)->body2);
	}
	ObjectManager::getManager()->elevators.erase(ObjectManager::getManager()->elevators.begin(),ObjectManager::getManager()->elevators.end());
	
	for(int i = 0; i < ObjectManager::getManager()->ropes.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->ropes.at(i)->body1);
		mWorld->DestroyBody(ObjectManager::getManager()->ropes.at(i)->body2);
	}
	ObjectManager::getManager()->ropes.erase(ObjectManager::getManager()->ropes.begin(),ObjectManager::getManager()->ropes.end());
	
	for(int i = 0; i < ObjectManager::getManager()->prismaticBoxes.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->prismaticBoxes.at(i)->boxBody1);
		mWorld->DestroyBody(ObjectManager::getManager()->prismaticBoxes.at(i)->boxBody2);
	}
	ObjectManager::getManager()->prismaticBoxes.erase(ObjectManager::getManager()->prismaticBoxes.begin(),ObjectManager::getManager()->prismaticBoxes.end());
	
	for(int i = 0; i < ObjectManager::getManager()->babyTurtles.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->babyTurtles.at(i)->body);
	}
	ObjectManager::getManager()->babyTurtles.erase(ObjectManager::getManager()->babyTurtles.begin(),ObjectManager::getManager()->babyTurtles.end());
	
	for(int i = 0; i < ObjectManager::getManager()->bridges.size(); i++)
	{
		for(int j=0; j < ObjectManager::getManager()->bridges.at(i)->Planks.size();j++)
		{
			mWorld->DestroyBody(ObjectManager::getManager()->bridges.at(i)->Planks.at(i));
		}
		ObjectManager::getManager()->bridges.at(i)->Planks.erase(ObjectManager::getManager()->bridges.at(i)->Planks.begin(),ObjectManager::getManager()->bridges.at(i)->Planks.end());
		mWorld->DestroyBody(ObjectManager::getManager()->bridges.at(i)->Anchor);
	}
	ObjectManager::getManager()->bridges.erase(ObjectManager::getManager()->bridges.begin(),ObjectManager::getManager()->bridges.end());
	
	for(int i = 0; i < ObjectManager::getManager()->gears.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->gears.at(i)->body1);
		mWorld->DestroyBody(ObjectManager::getManager()->gears.at(i)->body2);
	}
	ObjectManager::getManager()->gears.erase(ObjectManager::getManager()->gears.begin(),ObjectManager::getManager()->gears.end());
	
	for(int i = 0; i < ObjectManager::getManager()->nests.size(); i++)
	{
		if(ObjectManager::getManager()->nests.at(i)->mBody!=NULL)
			mWorld->DestroyBody(ObjectManager::getManager()->nests.at(i)->mBody);
	}
	ObjectManager::getManager()->nests.erase(ObjectManager::getManager()->nests.begin(),ObjectManager::getManager()->nests.end());

	
	for(int i = 0; i < ObjectManager::getManager()->pushableBlocks.size(); i++)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->pushableBlocks.at(i)->body);
	}
	ObjectManager::getManager()->pushableBlocks.erase(ObjectManager::getManager()->pushableBlocks.begin(),ObjectManager::getManager()->pushableBlocks.end());
	if(ObjectManager::getManager()->player!=NULL)
	{
		mWorld->DestroyBody(ObjectManager::getManager()->player->Body);
	}

	const int mapHeight = 34;
	const int mapLength = 112;

	const int blockWidth = 30;
	const int blockHeight = 30;

    string map[mapHeight]={
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnNnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnn000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnBnn0",
            "000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000000000000000000000000000000000",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnn0000000000000000000nn0nnnnnnnnnnnnn00000nnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnnn000nnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "0nnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnNnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnNn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnn0",
            "00nnnnnnnnnnnn000nnnnnnn0000000000000nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnn00nnnnnnnn0000000nnnnnnnnnnnnnnnnn00000",
            "00nnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn00000",
            "0000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn00000",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnn0nn0nnnnnnnnnnnnn0nnnnnnnnnnnnnnnnn0nnnnnnnCnnnnnnnnnn0nnnnnnnnnn00000",
            "0nnnnnnnn00nnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnn0nnnnnnnnnnnnn0000nnnnnn000000000000000000000000000nnn0000000000000",
            "0nnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnn0nnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000000000",
            "0nnnnnnnnnnnnn00000000000000000nnnnn0nnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000000000",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnn0nn0nnnnnnnnnnnnnnnnnnn00nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn00000000000000",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nn0nnn0nn0nnnnnn00000000000000000000000000000000000000000000000000000",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000nnn0000nnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0nnnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "000nnnnnnnnnnn00000000000000nn000000nnnnnnnnnnnnnnNnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "000nnnnnnnnnnnnnnnnnnnnnnnn0000nnnn0nnnnnnnnnnnnnnnnnnnnnnn0nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000000000000000000000nnnnnn0000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0000000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "00000000000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0000000nNnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn0",
            "0000000000000000000000000nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn000000000nnnnnnnnnnnnnnnnnnSnnnnnnnnnnnnn0000000",
			"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    };//nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn

    for(int x = 0; x < mapLength;x++)
	{
            for(int y = 0; y < mapHeight;y++)
			{
                    char c = map[y].at(x);
                    if(map[y].at(x)=='0')
					{
						ObjectManager::getManager()->platforms.push_back( Platform::CreatePlatform(x*blockWidth,y*blockHeight,blockWidth,blockHeight,mWorld));
                    }
					else if(map[y].at(x)=='S')
					{
						ObjectManager::getManager()->player = Player::CreatePlayer(x*blockWidth,y*blockHeight,mWorld);
					}
					else if(map[y].at(x)=='N')
					{
						ObjectManager::getManager()->nests.push_back(new Nest(b2Vec2(x*blockWidth,y*blockHeight),.2,mWorld,ObjectManager::getManager()->player));
					}
					else if(map[y].at(x)=='B')
					{
						ObjectManager::getManager()->butterfly = new Butterfly(x*blockWidth,y*blockHeight,ObjectManager::getManager()->player,mWorld);
					}
					else if(map[y].at(x)=='C')
					{
						ObjectManager::getManager()->catapults.push_back(new Catapult(x*blockWidth,y*blockHeight, 80, 20, mWorld));
					}
            }
    }
	ObjectManager::getManager()->bridges.push_back(new Bridge(mWorld,b2Vec2(1900,350), 5,50));
	ObjectManager::getManager()->pushableBlocks.push_back(new PushableBlock(820,200,25,25,7,mWorld));
	ObjectManager::getManager()->pushableBlocks.push_back(new PushableBlock(2535,400,30,30,1,mWorld));
	ObjectManager::getManager()->prismaticBoxes.push_back(new PrismaticBox(mWorld,b2Vec2(600,600),b2Vec2(500,750)));
	ObjectManager::getManager()->ropes.push_back(new Rope(mWorld,b2Vec2(300,150),b2Vec2(10,10),b2Vec2(300,300),b2Vec2(40,10),200.0f));
	ObjectManager::getManager()->elevators.push_back(new Elevator(mWorld,1510,700,50,20,1,1310,355,50,20,1,1510,200,1310,200));
	ObjectManager::getManager()->gears.push_back(GearPlatform::CreateGear(mWorld,b2Vec2(3300,920),b2Vec2(10,10),b2Vec2(3200,900),b2Vec2(30,10),b2Vec2(1,0)));
	//ObjectManager::getManager()->gears.push_back(GearPlatform::CreateGear(mWorld,b2Vec2(150,100),b2Vec2(10,10),b2Vec2(250,150),b2Vec2(30,10),b2Vec2(1,0)));

	SoundManager::getSoundManager()->playBackgroundMusic();
}

Game::~Game(void)
{
}


int Game::Update(std::clock_t timeElapsed)
{

	float32 timeStep = 1.0f / 10.0f;
	//float32 timeStep = 1.0f / 5.0f;


	int32 velocityIterations = 6;

	int32 positionIterations = 2;

	ObjectManager::getManager()->Update(timeElapsed);
	TotalTimeElapsed += timeElapsed;

	mWorld->Step(timeStep, velocityIterations, positionIterations);
	// Creation/ destrucion of joints can be done onlyafter world fihished simulation for this frame.  Beware
	//ObjectManager::getManager()->gears.at(0)->rotateClockwise();

	for (int i = 0; i< ObjectManager::getManager()->nests.size();i++)
	{
		if(ObjectManager::getManager()->nests.at(i)->mHatchEgg  && !ObjectManager::getManager()->nests.at(i)->mEggHatched){
			ObjectManager::getManager()->babyTurtles.push_back(ObjectManager::getManager()->nests.at(i)->MakeBaby(mWorld));
			ObjectManager::getManager()->nests.at(i)->mEggHatched = true;
			mWorld->DestroyBody(ObjectManager::getManager()->nests.at(i)->mBody);
		}
	}

	for (int i = 0; i< ObjectManager::getManager()->babyTurtles.size();i++)
	{
		if(ObjectManager::getManager()->babyTurtles.at(i)->dead)
		{
			mWorld->DestroyBody(ObjectManager::getManager()->babyTurtles.at(i)->body);
			vector<BabyTurtle*>::iterator iter = ObjectManager::getManager()->babyTurtles.begin();
			for(int j = 0; j<i;j++)
			{
				iter++;
			}
			ObjectManager::getManager()->babyTurtles.erase(iter);
		}
	}
	if(ObjectManager::getManager()->butterfly->health <= 0)
	{
		return 1;
	}
	if(ObjectManager::getManager()->player->dead)
	{
		return 2;
	}

	return 0;
}


void Game::Draw()
{
	ObjectManager::getManager()->Draw(mRenderer);
}

void Game::setupGameMap(){}