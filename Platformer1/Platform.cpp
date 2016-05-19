#include "Platform.h"


Platform* Platform::CreatePlatform(float x,float y,float width,float height, b2World* world)
{
	return new Platform( x, y, width, height, world);
}



Platform::Platform(float x, float y, float width,float height, b2World* world):mWidth(width),mHeight(height){
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className="platform";

	Body = BodyFactory::createBody(world,x,y,mWidth,mHeight,0,1,false,false,myColIdent,1,1|2|3);

}






Platform::~Platform(void)
{
}

void Platform::render(SDL_Renderer* renderer, SDL_Texture* texture,b2Vec2 offset)
{
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float size = 0;
	float count = 0;
	float rotation = (Body->GetAngle()*180.0/3.14159265);
	if(mWidth<mHeight)
	{
		size = mWidth;
		count = mHeight/mWidth;
		
		for(int i = 0; i < count;i++)
		{
			
			stretchRect.x = Body->GetPosition().x-offset.x-(mWidth/2.0f)+(sin(-Body->GetAngle())*(mWidth*i)); 
			stretchRect.y = Body->GetPosition().y-offset.y-(mHeight/2.0f)+(cos(Body->GetAngle())*(mWidth*i)); 
	
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
			stretchRect.x = Body->GetPosition().x-offset.x-(mWidth/2.0f)+(cos(-Body->GetAngle())*(mHeight*i)); 
			stretchRect.y = Body->GetPosition().y-offset.y-(mHeight/2.0f)+(sin(Body->GetAngle())*(mHeight*i)); 
	
			stretchRect.w = mHeight; 
			stretchRect.h = mHeight;
			//render image
	
			SDL_RenderCopyEx ( renderer, texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}
	//to draw image at correct position
}