#ifndef NECROENTITY_H
#define NECROENTITY_H

#include "Vector2.h"
#include "Image.h"

class Cell;

//-----------------------------------------------------------------------------
// An Enity is the base unit of something that exists inside of a Cell.
//-----------------------------------------------------------------------------
class Entity
{
	friend class Animator; // Animator is a friend class of Entity

private:
	static uint32_t ENT_NEXT_ID; // EntityID static track

protected:
	uint32_t ID;				// EntityID

	Image* img;
	Cell* owner;				// Owner of this entity

	// Used for entities that uses tilesets, index of X and Y, they will be multiplied by img->GetTileset().tileWidth and img->GetTileset().tileHeight
	int tilesetXOff, tilesetYOff;

public:
	Entity();
	Entity(Vector2 pInitialPos, Image* pImg);

	Vector2 pos;				// orthographic pos
	int gridPosX, gridPosY;		// Position in the gridmap

	Vector2 isoPos;				// isometric pos (used only for rendering)

public:
	const uint32_t	GetID() const;

	void			SetImg(Image* pImg);
	void			SetOwner(Cell* c);
	void			ClearOwner();
	void			TransferToCell(Cell* c);		// Transfer this entity to exist in another cell 

	virtual void	Update();
	void			Draw();
};

inline const uint32_t Entity::GetID() const
{
	return ID;
}

#endif
