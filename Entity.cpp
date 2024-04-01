#include "NECROEngine.h"

#include "Entity.h"
#include "Utility.h"

uint32_t Entity::ENT_NEXT_ID = 0;

Entity::Entity()
{
	ID = ENT_NEXT_ID;
	ENT_NEXT_ID++;

	img = nullptr;
	owner = nullptr;
	tilesetXOff = tilesetYOff = 0;
	gridPosX = gridPosY = 0;
}

Entity::Entity(Vector2 pInitialPos, Image* pImg)
{
	ID = ENT_NEXT_ID;
	ENT_NEXT_ID++;

	pos = pInitialPos;
	gridPosX = pos.x / CELL_WIDTH;
	gridPosY = pos.y / CELL_HEIGHT;

	SetImg(pImg);
}

//------------------------------------------------------------
// Sets the Image of this Entity
//------------------------------------------------------------
void Entity::SetImg(Image* pImg)
{
	img = pImg;
}

//------------------------------------------------------------
// Sets the owner of this Entity
//------------------------------------------------------------
void Entity::SetOwner(Cell* c)
{
	owner = c;
}

//------------------------------------------------------------
// Clears the owner of this entity
//------------------------------------------------------------
void Entity::ClearOwner()
{
	owner = nullptr;
}

//----------------------------------------------------------------------------------------------
// Moves the entity to the cell specified in the argument,
// removing the Ptr present in the previous owner's vector
// 
// Immediately: does the transfer right away, (as for now, as soon as Entity::Update is called)
// If the entities are updated from looping over the worldmap, THIS MUST NOT BE USED, 
// if an entity moves fast enough downwards (or framerate is low), the entity can be updated 
// multiple times (from cell [0][0] to [4][4], and re-updated from [4][4] to [8][8], and so on)
// 
// Use TransferToCellQueue to let the world perform the transfer AFTER a world update completes.
// This function will be called by the World with nullptr as argument
//----------------------------------------------------------------------------------------------
void Entity::TransferToCellImmediately(Cell* c)
{
	// If this is called with nullptr as argument, the transfer is supposed to be in nextOwner
	if (c == nullptr && nextOwner)
		c = nextOwner;

	// Remove Ptr from previous owner
	owner->RemoveEntityPtr(ID);

	// Update owner
	SetOwner(c);

	// Add Ptr to current owner
	c->AddEntityPtr(this);

	nextOwner = nullptr;
}

void Entity::TransferToCellQueue(Cell* c)
{
	nextOwner = c;
	owner->GetWorld()->AddPendingEntityToTransfer(this);
}

//------------------------------------------------------------
// Updates the Entity
//------------------------------------------------------------
void Entity::Update()
{
	// Update grid position
	gridPosX = pos.x / CELL_WIDTH;
	gridPosY = pos.y / CELL_HEIGHT;

	// Update ISO coordinates
	NMath::CartToIso(pos.x / CELL_WIDTH, pos.y / CELL_HEIGHT, isoPos.x, isoPos.y);

	isoPos.x -= HALF_CELL_WIDTH;

	// Adjust isoX and isoY to the world offset
	isoPos.x += engine.GetGame().GetMainCamera()->pos.x;
	isoPos.y += engine.GetGame().GetMainCamera()->pos.y;

	if (!img->IsTileset())
		isoPos.y -= img->GetHeight();
	else
		isoPos.y -= img->GetTilesetHeight();

	// Account for the Y offset of the image
	isoPos.x += img->GetXOffset();
	isoPos.y += img->GetYOffset();

	// TODO: may not have to update collider here for static entities, but need to properly set them
	if (coll.enabled)
		coll.Update();
}

//------------------------------------------------------------
// Draws the Entity
//------------------------------------------------------------
void Entity::Draw()
{
	if (!img->IsTileset())
	{
		SDL_Rect dstRect = { static_cast<int>(isoPos.x), static_cast<int>(isoPos.y), img->GetWidth(), img->GetHeight() };
		engine.GetRenderer().DrawImageDirectly(img->GetSrc(), NULL, &dstRect);
	}
	else
	{
		Image::Tileset tset = img->GetTileset();
		SDL_Rect srcRect = { tilesetXOff * tset.tileWidth, tilesetYOff * tset.tileHeight, tset.tileWidth, tset.tileHeight };
		SDL_Rect dstRect = { static_cast<int>(isoPos.x), static_cast<int>(isoPos.y), tset.tileWidth, tset.tileHeight };
		engine.GetRenderer().DrawImageDirectly(img->GetSrc(), &srcRect, &dstRect);
	}

	if (coll.enabled) // && debug collider
		coll.DebugDraw();
}
