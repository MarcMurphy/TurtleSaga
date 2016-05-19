#include "ObjectManager.h"

ObjectManager* ObjectManager::me;

ObjectManager* ObjectManager::getManager()
{
	if(me==NULL){
		me=new ObjectManager();
	}
	return me;
}

ObjectManager::ObjectManager(void)
{
	player = NULL;
}


ObjectManager::~ObjectManager(void)
{
}


void ObjectManager::Update(float timeElapsed)
{
	player->Update(timeElapsed);
	butterfly->Update(timeElapsed);
	for(int i = 0; i < babyTurtles.size(); i++)
	{
		if(i==0)
		{
			babyTurtles.at(i)->Update(player->Body,butterfly->Body,timeElapsed);
		}
		else
		{
			babyTurtles.at(i)->Update(babyTurtles.at(i-1)->body,butterfly->Body,timeElapsed);
		}
	}
	for(int i = 0; i < trees.size(); i++)
	{
		trees.at(i)->Update(timeElapsed);
	}
		

}


void ObjectManager::Draw(SDL_Renderer* renderer)
{
	SDL_RenderClear( renderer );
	b2Vec2 offset = b2Vec2(player->Body->GetPosition().x-320,player->Body->GetPosition().y-240);
	
	SDL_Rect stretchRect; 
	b2Vec2 backgroundPos;
	
	for(int i = -1; i < 2; i++)
	{
		for(int j = 1; j < 4; j++)
		{
			backgroundPos = -offset;
			stretchRect.x = backgroundPos.x+(i*(640-14)); 
			stretchRect.y = backgroundPos.y-(480*j); 
			stretchRect.w = 640; 
			stretchRect.h = 480;
			while(stretchRect.y>900)
			{
				stretchRect.y-= (480)*3;
			}
			while(stretchRect.x>1200)
			{
				stretchRect.x-= (640-14)*3;
			}
			while(stretchRect.x<-700)
			{
				stretchRect.x+= (640-14)*3;
			}
			SDL_RenderCopyEx ( renderer, TextureManager::getManager()->backgroundSkyTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}
	for(int i = -1; i < 2; i++)
	{
		backgroundPos = -offset;
		stretchRect.x = backgroundPos.x+(i*(640-14)); 
		stretchRect.y = backgroundPos.y; 
		stretchRect.w = 640; 
		stretchRect.h = 480;
		while(stretchRect.x>1200)
		{
			stretchRect.x-= (640-14)*3;
		}
		while(stretchRect.x<-700)
		{
			stretchRect.x+= (640-14)*3;
		}
		SDL_RenderCopyEx ( renderer, TextureManager::getManager()->backgroundTreesTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
	}
	for(int i = -1; i < 2; i++)
	{
		for(int j = 1; j < 4; j++)
		{
			backgroundPos = -offset;
			stretchRect.x = backgroundPos.x+(i*(640-14)); 
			stretchRect.y = backgroundPos.y+(480*j); 
			stretchRect.w = 640; 
			stretchRect.h = 480;
			while(stretchRect.y<-500)
			{
				stretchRect.y+= (480)*3;
			}
			while(stretchRect.x>1200)
			{
				stretchRect.x-= (640-14)*3;
			}
			while(stretchRect.x<-700)
			{
				stretchRect.x+= (640-14)*3;
		}
			SDL_RenderCopyEx ( renderer, TextureManager::getManager()->backgroundEarthTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
		}
	}

	//SDL_RenderCopyEx ( renderer, TextureManager::getManager()->backgroundTreesTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

	//stretchRect.x = 640-14; 	
	
	//SDL_RenderCopyEx ( renderer, TextureManager::getManager()->backgroundTreesTexture, NULL, &stretchRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE );

	
	for(int i = 0; i < bridges.size(); i++)
	{
		bridges.at(i)->render(renderer,TextureManager::getManager()->baseTexture,offset);
	}
	SDL_Texture* babyTexture;
	for(int i = 0; i < babyTurtles.size(); i++)
	{
		if(babyTurtles.at(i)->walk[babyTurtles.at(i)->imgNum]==0)
			babyTexture = TextureManager::getManager()->babyWalk1Texture;
		if(babyTurtles.at(i)->walk[babyTurtles.at(i)->imgNum]==1)
			babyTexture = TextureManager::getManager()->babyWalk2Texture;
		if(babyTurtles.at(i)->walk[babyTurtles.at(i)->imgNum]==2)
			babyTexture = TextureManager::getManager()->babyWalk3Texture;
		babyTurtles.at(i)->render(renderer,babyTexture,offset);
	}


	SDL_Texture* playerTexture = TextureManager::getManager()->playerStandTexture;
	
	if(player->isBlocking)
	{
		playerTexture = TextureManager::getManager()->playerBlockTexture;
	}
	else
	{
		if(KeyHandler::getKeys()->Key_Left||KeyHandler::getKeys()->Key_Right)
		{
			if(player->walk[player->imgNum]==0)
				playerTexture = TextureManager::getManager()->playerWalk1Texture;
			if(player->walk[player->imgNum]==1)
				playerTexture = TextureManager::getManager()->playerStandTexture;
			if(player->walk[player->imgNum]==2)
				playerTexture = TextureManager::getManager()->playerWalk2Texture;
		}
		if(player->jumpCharge!=0)
		{
			playerTexture = TextureManager::getManager()->playerCrouchTexture;
		}
	}
	player->render(renderer,playerTexture,offset);
	for(int i = 0; i < elevators.size(); i++)
	{
		elevators.at(i)->render(renderer,TextureManager::getManager()->pulleyTexture,TextureManager::getManager()->pulleyWheelTexture,TextureManager::getManager()->pulleyRopeTexture,TextureManager::getManager()->ropeTexture,offset);
	}
	for(int i = 0; i < trees.size(); i++)
	{
		trees.at(i)->Draw(renderer,TextureManager::getManager()->treeBottomTexture,TextureManager::getManager()->treeMiddleTexture,TextureManager::getManager()->treeTopTexture,offset);
	}
	for(int i = 0; i < ropes.size(); i++)
	{
		ropes.at(i)->render(renderer,TextureManager::getManager()->blockTexture,TextureManager::getManager()->ropeTexture,offset);
	}
	for(int i = 0; i < prismaticBoxes.size(); i++)
	{
		prismaticBoxes.at(i)->render(renderer,TextureManager::getManager()->prismaticBlockTexture,offset);
	}
	for(int i = 0; i < platforms.size(); i++)
	{
		platforms.at(i)->render(renderer,TextureManager::getManager()->blockTexture,offset);
	}
	for(int i = 0; i < catapults.size(); i++)
	{
		catapults.at(i)->render(renderer,
								TextureManager::getManager()->catapultBase,
								TextureManager::getManager()->catapultBlock,
								TextureManager::getManager()->catapultWheel,
								TextureManager::getManager()->catapultBeam,
								TextureManager::getManager()->catapultArm,offset);
	}
	for(int i = 0; i < gears.size(); i++)
	{
		gears.at(i)->render(renderer,TextureManager::getManager()->baseTexture,offset);
	}
	for(int i = 0; i < nests.size(); i++)
	{
		nests.at(i)->Draw(renderer,TextureManager::getManager()->nestNormalTexture,TextureManager::getManager()->nestHatchedTexture,offset);
	}
	for(int i = 0; i < pushableBlocks.size(); i++)
	{
		pushableBlocks.at(i)->render(renderer,TextureManager::getManager()->pushBlockTexture,offset);
	}
	
	if(butterfly->frame %2 ==0){
		butterfly->render(renderer,TextureManager::getManager()->butterflyIdleTexture1,TextureManager::getManager()->healthbar,TextureManager::getManager()->health,offset);
	}
	else{
		butterfly->render(renderer,TextureManager::getManager()->butterflyIdleTexture2,TextureManager::getManager()->healthbar,TextureManager::getManager()->health,offset);
	}
	
	
	
	SDL_RenderPresent( renderer );
}