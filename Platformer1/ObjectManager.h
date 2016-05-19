#pragma once
#include "Player.h"
#include "Platform.h"
#include <vector>
#include "SDL.h"
#include "TextureManager.h"
#include "Elevator.h"
#include "Catapult.h"
#include "Tree.h"
#include "Rope.h"
#include "PrismaticBox.h"
#include "PressureSwitch.h"
#include "Bridge.h"
#include "BabyTurtle.h"
#include "GearPlatform.h"
#include "Nest.h"
#include "PushableBlock.h"
#include "Butterfly.h"

class ObjectManager
{
private:
	static ObjectManager* me;
public:
	static ObjectManager* getManager();
	ObjectManager(void);
	~ObjectManager(void);
	Player* player;
	vector<Catapult*> catapults;
	vector<Platform*> platforms;
	vector<Tree*> trees;
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer);
	vector<Elevator*> elevators;
	vector<Rope*> ropes;
	vector<PrismaticBox*> prismaticBoxes;
	vector<BabyTurtle*> babyTurtles;
	vector<Bridge*> bridges;
	vector<GearPlatform*> gears;
	vector<Nest*> nests;
	vector<PushableBlock*> pushableBlocks;
	Butterfly* butterfly;
};

