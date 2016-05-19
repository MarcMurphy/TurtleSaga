#pragma once
#include "SDL.h"
class TextureManager
{
private:
	static TextureManager* me;
public:
	static TextureManager* getManager();
	TextureManager(void);
	~TextureManager(void);

	SDL_Texture* baseTexture;
	SDL_Texture* treeTexture;


	SDL_Texture* playerStandTexture;
	SDL_Texture* playerWalk1Texture;
	SDL_Texture* playerWalk2Texture;
	SDL_Texture* playerCrouchTexture;
	SDL_Texture* playerBlockTexture;

	SDL_Texture* butterflyIdleTexture1;
	SDL_Texture* butterflyIdleTexture2;

	SDL_Texture* treeBottomTexture;
	SDL_Texture* treeMiddleTexture;
	SDL_Texture* treeTopTexture;

	
	SDL_Texture* backgroundTreesTexture;
	SDL_Texture* backgroundSkyTexture;
	SDL_Texture* backgroundEarthTexture;

	
	SDL_Texture* babyWalk1Texture;
	SDL_Texture* babyWalk2Texture;
	SDL_Texture* babyWalk3Texture;

	SDL_Texture* blockTexture;
	SDL_Texture* pushBlockTexture;
	SDL_Texture* prismaticBlockTexture;
	SDL_Texture* ropeTexture;
	SDL_Texture* pulleyWheelTexture;
	SDL_Texture* pulleyTexture;
	SDL_Texture* pulleyRopeTexture;
	SDL_Texture* nestHatchedTexture;
	SDL_Texture* nestNormalTexture;

	SDL_Texture* mainMenu;
	SDL_Texture* endScreen;
	SDL_Texture* deathScreen;


	SDL_Texture* catapultBase;
	SDL_Texture* catapultBlock;
	SDL_Texture* catapultWheel;
	SDL_Texture* catapultBeam;
	SDL_Texture* catapultArm;

	SDL_Texture* healthbar;
	SDL_Texture* health;
};

