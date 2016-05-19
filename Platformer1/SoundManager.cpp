#include "SoundManager.h"


SoundManager* SoundManager::me;

SoundManager* SoundManager::getSoundManager()
{
	if(me == NULL)
	{
		Mix_AllocateChannels(99999 );
		me = new SoundManager();
	}
	return me;
}

SoundManager::SoundManager(void){
	
	eggHatching = Mix_LoadWAV("egghatching.wav");
	treeShatter = Mix_LoadWAV("treeshatter.wav");

	
	treeLaunch = Mix_LoadWAV("shoot.wav");
	
	jump = Mix_LoadWAV( "jump.wav" );

	backgroundMusic = Mix_LoadWAV("background.wav");
}


SoundManager::~SoundManager(void)
{
}

void SoundManager::playEggHatching(void){
	Mix_PlayChannel( -1, eggHatching, 0 );
}
void SoundManager::playJump(void){
	Mix_PlayChannel( -1, jump, 0 );
}
void SoundManager::playTreeLaunch(void){
	Mix_PlayChannel( -1, treeLaunch, 0 );
}

void SoundManager::playTreeShatter(void){
	Mix_PlayChannel( -1, treeShatter, 0 );
}

void SoundManager::playBackgroundMusic(void){
	Mix_PlayChannel(-1,backgroundMusic,10);
}