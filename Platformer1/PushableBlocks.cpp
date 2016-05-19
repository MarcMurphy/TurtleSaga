#include "PushableBlock.h"




PushableBlock::PushableBlock(float x,float y, float width, float height, float density, b2World* world):mWidth(width),mHeight(height){
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="pushBlock";
	
	body = BodyFactory::createBody(world,x,y,mWidth,mHeight,density,0.25f,true,true,myColIdent,3,1);
}


void PushableBlock::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float size = 0;
	float count = 0;
	float rotation = (body->GetAngle()*180.0/3.14159265);
	if(mWidth<mHeight)
	{
		size = mWidth;
		count = mHeight/mWidth;
		
		for(int i = 0; i < count;i++)
		{
			stretchRect.x = body->GetPosition().x-offset.x-(mWidth/2.0f)+(sin(-body->GetAngle())*(mWidth*i)); 
			stretchRect.y = body->GetPosition().y-offset.y-(mHeight/2.0f)+(cos(body->GetAngle())*(mWidth*i)); 
	
			stretchRect.w = mWidth; 
			stretchRect.h = mWidth;
			//render image
	
			SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}
	else
	{
		size = mHeight;
		count = mWidth/mHeight;

		for(int i = 0; i < count;i++)
		{
			stretchRect.x = body->GetPosition().x-offset.x-(mWidth/2.0f)+(cos(-body->GetAngle())*(mHeight*i)); 
			stretchRect.y = body->GetPosition().y-offset.y-(mHeight/2.0f)+(sin(body->GetAngle())*(mHeight*i)); 
	
			stretchRect.w = mHeight; 
			stretchRect.h = mHeight;
			//render image
	
			SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}
	//to draw image at correct position
}

