#include "KeyHandler.h"


KeyHandler* KeyHandler::me;
bool KeyHandler::Key_Left;
bool KeyHandler::Key_Right;
bool KeyHandler::Key_Up;
bool KeyHandler::Key_Space;
bool KeyHandler::Key_Down;
bool KeyHandler::Key_S;
bool KeyHandler::Key_R;
bool KeyHandler::Key_Q;
bool KeyHandler::QUIT;


KeyHandler* KeyHandler::getKeys()
{
	if(me==NULL)
	{
		me=new KeyHandler();
		Key_Left=false;
		Key_Right=false;
		Key_Up=false;
		Key_Space=false;
		Key_Down=false;
		Key_S=false;
		Key_Q=false;
		Key_R=false;
		QUIT=false;
	}
	return me;
}

KeyHandler::KeyHandler(void)
{
}


KeyHandler::~KeyHandler(void)
{
}

void KeyHandler::Update(SDL_Event eHandler)
{
	while( SDL_PollEvent( &eHandler ) != 0 ) 
	{ 
		if( eHandler.type == SDL_QUIT ) 
		{ 
			QUIT = true; 
		} 
		else if( eHandler.type == SDL_KEYDOWN )
		{ 
			switch( eHandler.key.keysym.sym )
			{
			case SDLK_ESCAPE: 
				QUIT = true;
				break; 
			case SDLK_UP:
				Key_Up=true;
				break; 
			case SDLK_DOWN:
				Key_Down=true;
				break; 
			case SDLK_LEFT:
				Key_Left=true;
				break; 
			case SDLK_RIGHT:
				Key_Right=true;
				break; 
			case SDLK_SPACE:
				Key_Space=true;
				break; 
			case SDLK_s:
				Key_S=true;
				break;
			case SDLK_q:
				Key_Q=true;
				break; 
			case SDLK_r:
				Key_R=true;
				break;
			default: 
				break; 
			}
		}
		else if( eHandler.type == SDL_KEYUP )
		{ 
			switch( eHandler.key.keysym.sym )
			{
			case SDLK_ESCAPE: 
				QUIT = false;
				break; 
			case SDLK_UP:
				Key_Up=false;
				break; 
			case SDLK_DOWN:
				Key_Down=false;
				break; 
			case SDLK_LEFT:
				Key_Left=false;
				break; 
			case SDLK_RIGHT:
				Key_Right=false;
				break; 
			case SDLK_SPACE:
				Key_Space=false;
				break; 
			case SDLK_s:
				Key_S=false;
				break;
			case SDLK_q:
				Key_Q=false;
				break; 
			case SDLK_r:
				Key_R=false;
				break;
			default: 
				break; 
			}
		}
	}							
}