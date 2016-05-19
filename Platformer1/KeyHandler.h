#pragma once
#include <stddef.h>
#include "SDL.h"
using namespace std;
class KeyHandler
{
private:
	static KeyHandler* me;

public:
	static KeyHandler* getKeys();
	static bool Key_Left;
	static bool Key_Right;
	static bool Key_Up;
	static bool Key_Space;
	static bool Key_Down;
	static bool Key_S;
	static bool Key_Q;
	static bool Key_R;

	static bool KeyHandler::QUIT;
	void Update(SDL_Event eHandler);
	KeyHandler(void);
	~KeyHandler(void);
};

