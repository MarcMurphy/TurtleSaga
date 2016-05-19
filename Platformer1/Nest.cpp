#include "Nest.h"


Nest::Nest(b2Vec2 position,float scale, b2World* world, Player*player):
m_position(position),
mEggHatched(false),
mHatchEgg(false),
mSizeWithEgg(b2Vec2(488,273)),
mSizeWithoutEgg(b2Vec2(488,273)),
mScale(scale),
mRadius((mSizeWithEgg.x*mScale)/2),
mPlayer(player)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="nest";
	mBody =  BodyFactory::createBody(world,m_position.x,m_position.y,mSizeWithEgg.x * mScale,mSizeWithEgg.y* mScale,0.25,1,false,false,myColIdent,3,1);


}

void Nest::Draw(SDL_Renderer* renderer, SDL_Texture* textureNormal,  SDL_Texture* textureHatched,b2Vec2 offset){
	SDL_Rect stretchRect; 

	stretchRect.x = m_position.x - offset.x-((mSizeWithEgg.x*mScale)/2); 
	stretchRect.y = m_position.y - offset.y; 

	if (mEggHatched){
		stretchRect.w = mSizeWithoutEgg.x*mScale; 
		stretchRect.h = mSizeWithoutEgg.y*mScale;
		SDL_RenderCopyEx (renderer, textureHatched, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
	else if (!mEggHatched){
		stretchRect.w = mSizeWithEgg.x*mScale; 
		stretchRect.h = mSizeWithEgg.y*mScale;
		SDL_RenderCopyEx (renderer, textureNormal, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
}
void Nest::Update(float time){

}


BabyTurtle* Nest::MakeBaby(b2World* world){
	SoundManager::getSoundManager()->playEggHatching();
	return new BabyTurtle(m_position.x,m_position.y,world);
}


