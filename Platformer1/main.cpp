#include "SDL.h"
#include "Box2D\Box2D.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "Game.h"
#include <iostream>
#include <ctime>
#include "ContactListener.h"
#include "KeyHandler.h"
#include "TextureManager.h"

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;
//The window we'll be rendering to 
SDL_Window* window = NULL; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = NULL; 
//Current displayed texture 
bool createdWorld = false;
SDL_Rect stretchRect; 
		






enum States{Menu,
			Gameplay,
			Wasted,
			Finished};

States state = Menu;
Game game;

//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );

bool init() 
{ 
	//Initialization flag 
	bool success = true; 

	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = SCREEN_WIDTH; 
	stretchRect.h = SCREEN_HEIGHT;




	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{  
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
        {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
		}
		
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow( "Platformer 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{ 
			//Create renderer for window 
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
			if( renderer == NULL ) 
			{ 
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
				success = false;
			} 
			else 
			{ 
				//Initialize renderer color 
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG; 
				if( !( IMG_Init( imgFlags ) & imgFlags  ) ) 
				{ 
					string a = IMG_GetError();
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; 
				} 
			} 
		}
	} 
	return success; 
}



SDL_Texture* loadTexture( std::string path ) 
{ 
	//The final texture 
	SDL_Texture* newTexture = NULL; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{
		//Create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		if( newTexture == NULL ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}


bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 
	//Load splash image 


	TextureManager::getManager()->baseTexture = loadTexture("TestImage.png");
	TextureManager::getManager()->treeTexture = loadTexture("tree.png");

	TextureManager::getManager()->playerStandTexture = loadTexture("sheltex.png");
	TextureManager::getManager()->playerCrouchTexture = loadTexture("Crouchturtle.png");
	TextureManager::getManager()->playerWalk1Texture = loadTexture("walk1.png");
	TextureManager::getManager()->playerWalk2Texture = loadTexture("walk2.png");
	TextureManager::getManager()->playerBlockTexture = loadTexture("turtleblock.png");
	
	TextureManager::getManager()->butterflyIdleTexture1 = loadTexture("Butterfly1.png");
	TextureManager::getManager()->butterflyIdleTexture2 = loadTexture("Butterfly2.png");

	TextureManager::getManager()->babyWalk1Texture = loadTexture("minionfly1.png");
	TextureManager::getManager()->babyWalk2Texture = loadTexture("minionfly2.png");
	TextureManager::getManager()->babyWalk3Texture = loadTexture("minionfly3.png");


	TextureManager::getManager()->blockTexture = loadTexture("BLOCK.png");
	TextureManager::getManager()->pushBlockTexture = loadTexture("woodbox.png");
	TextureManager::getManager()->prismaticBlockTexture = loadTexture("prismatic1.png");
	TextureManager::getManager()->backgroundTreesTexture = loadTexture("land.png");
	TextureManager::getManager()->backgroundEarthTexture = loadTexture("underground.png");
	TextureManager::getManager()->backgroundSkyTexture = loadTexture("sky.png");
	TextureManager::getManager()->ropeTexture = loadTexture("rope.png");
	TextureManager::getManager()->pulleyWheelTexture = loadTexture("pullywheel.png");
	TextureManager::getManager()->pulleyTexture = loadTexture("pullyplatform.png");
	TextureManager::getManager()->pulleyRopeTexture = loadTexture("trirope.png");

	TextureManager::getManager()->treeBottomTexture = loadTexture("treeBottom.png");
	TextureManager::getManager()->treeMiddleTexture = loadTexture("treeMiddle.png");
	TextureManager::getManager()->treeTopTexture = loadTexture("treeTop.png");
	TextureManager::getManager()->nestHatchedTexture = loadTexture("nestbroke.png");
	TextureManager::getManager()->nestNormalTexture = loadTexture("nest.png");
	
	TextureManager::getManager()->catapultBase = loadTexture("80x20px.png");
	TextureManager::getManager()->catapultBlock = loadTexture("20x20.png");
	TextureManager::getManager()->catapultWheel = loadTexture("r10px.png");
	TextureManager::getManager()->catapultBeam = loadTexture("10x20.png");
	TextureManager::getManager()->catapultArm = loadTexture("80x10arm.png");

	TextureManager::getManager()->mainMenu = loadTexture("START-MENU.png");
	TextureManager::getManager()->endScreen = loadTexture("WINSCREEN.png");
	TextureManager::getManager()->deathScreen = loadTexture("END-MENU.png");

		
	TextureManager::getManager()->healthbar = loadTexture("healthbar.png");
	TextureManager::getManager()->health = loadTexture("red.png");



	return success; 
}






void close() 
{ 
	//Free loaded image 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = NULL; 
	renderer = NULL; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();
}



int main( int argc, char* args[] ) 
{ 
	bool QUIT = false;
	if( !init() ){ 
		printf( "Failed to initialize!\n" ); 
	} 
	else { 
		//Load media 
		if( !loadMedia() )	{
			printf( "Failed to load media!\n" );
		}
		else{
			std::clock_t mClock;
			mClock = std::clock();
			while(!QUIT){

				KeyHandler::getKeys()->Update(eHandler);
				
				if(state==Menu){
					QUIT = KeyHandler::getKeys()->QUIT;
					if (KeyHandler::getKeys()->Key_Space){
						state= Gameplay;
						if(createdWorld)game.LevelBuilder();
					}
				}
			
				if(state== Finished){
					QUIT = KeyHandler::getKeys()->QUIT;
					if (KeyHandler::getKeys()->Key_Space){
						QUIT = true;
					}
				}

				if(state== Wasted)
				{
					QUIT = KeyHandler::getKeys()->QUIT;
					if (KeyHandler::getKeys()->Key_Space)
					{
						QUIT = true;
					}
				}

				if(state== Gameplay){
					if(!createdWorld){
						b2Vec2 gravity =  b2Vec2(0.0f,1.0f);
						bool doSleep = true;
						b2World* world = new b2World(gravity);
						world->SetContactListener(ContactListener::createListener());
						game = Game(renderer,world);
						createdWorld = true;
					}

	
					if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/240.0){
						int num = game.Update(std::clock()-mClock);
						mClock = std::clock();
						if(num == 1)
						{
							state = Finished;
						}
						if(num == 2)
						{
							state = Wasted;
						}
					}
					QUIT = KeyHandler::getKeys()->QUIT;
				}



				switch (state){
				case Menu:
					SDL_RenderClear( renderer ); 
					SDL_RenderCopy( renderer, TextureManager::getManager()->mainMenu, NULL, &stretchRect ); 
					SDL_RenderPresent( renderer );
					break;
				case Finished:
					SDL_RenderClear( renderer ); 
					SDL_RenderCopy( renderer, TextureManager::getManager()->endScreen, NULL, &stretchRect ); 
					SDL_RenderPresent( renderer );
					break;
				case Wasted:
					SDL_RenderClear( renderer ); 
					SDL_RenderCopy( renderer, TextureManager::getManager()->deathScreen, NULL, &stretchRect ); 
					SDL_RenderPresent( renderer );
					break;
				case Gameplay:
					game.Draw();
					break;
				}


			}
		}
	}
	close();
	return 0;
}