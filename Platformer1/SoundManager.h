#pragma once
//#include <SDL_mixer.h>
#include <SDL_mixer.h>
class SoundManager
{
public:
	static SoundManager* me;
	static SoundManager* getSoundManager();
	SoundManager(void);
	~SoundManager(void);
	void playJump(void);
	void playEggHatching(void);
	void playTreeLaunch(void);
	void playTreeShatter(void);
	void playBackgroundMusic(void);
	Mix_Chunk *jump;
	Mix_Chunk *eggHatching;
	Mix_Chunk *treeLaunch;
	Mix_Chunk *treeShatter;

	Mix_Chunk *backgroundMusic;
};

