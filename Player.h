#ifndef NECROPLAYER_H
#define NECROPLAYER_H

#include "Entity.h"
#include "Game.h"
#include "Animator.h"
#include "Collider.h"

const float PLAYER_MOVE_SPEED_FREE = 180.0f;
const float PLAYER_MOVE_SPEED_AIM = 100.0f;

//-------------------------------------------------
// Player class, derived by Entity
//-------------------------------------------------
class Player : public Entity
{
private:
	Animator anim;

	float curMoveSpeed = 2.5f;
	IsoDirection isoDirection = IsoDirection::WEST;			// The isometric direction the player is facing

	float deltaX = 0.0f, deltaY = 0.0f;


	bool wasAiming = false;
	bool isAiming = false;									// Is the player in aim mode?

	bool wasMoving = false;
	bool isMoving = false;

	float relativeMouseX, relativeMouseY;

	// List of close (8-neighbours close) entities, filled every frame
	std::vector<Entity*> closeEntities;

private:
	void			CalculateIsoDirection(float deltaX, float deltaY);
	void			CalculateIsoDirectionWhileAiming();
	void			HandleMovements();

	void			UpdateCloseEntities();

public:
	bool			controlsEnabled = true; // TEST: 

	void			Init();

	void			HandleAnim();
	virtual void	Update() override;

	float			GetCurMoveSpeed() const;
};

inline float Player::GetCurMoveSpeed() const
{
	return curMoveSpeed;
}

#endif
