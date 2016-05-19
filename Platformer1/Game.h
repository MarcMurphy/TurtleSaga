
#pragma once
#include "Box2D\Box2D.h"
#include "SDL.h"
#include <ctime>
#include <string>
#include "Platform.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Tree.h"
#include "PrismaticBox.h"
#include "PushableBlock.h"

using namespace std;

class Game
{
private:
public:
    void setupGameMap();
	static bool victory;
	Game();
	std::clock_t TotalTimeElapsed;
	b2World* mWorld;
	Game(SDL_Renderer* renderer,b2World* world);
	~Game(void);
	void LevelBuilder();
	SDL_Renderer* mRenderer;
	int Update(std::clock_t timeElapsed);
	void Draw();

	
};

