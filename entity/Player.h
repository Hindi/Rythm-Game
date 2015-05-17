#pragma once

#include "Entity.h"

#include "..\utility\EventManager.hpp"
#include "..\media\animations\Frame.h"
#include "..\media\animations\Anim.h"
#include "..\media\animations\Animation.h"
#include "..\media\animations\AnimationManager.h"
#include "..\media\MediaManager.hpp"

/**
 * @enum	JumpState
 *
 * @brief	Used to update the animation when the player is jumping
 */

enum JumpState
{
	NotJumping,
	StartJump,
	ReachingTop,
	LeavingTop,
	FallingDown,
	Landing
};

/**
 * @class	Player
 *
 * @brief	The Player, inherits Entity
 *
 */

class Player : public Entity
{
public:
	
#pragma region constructeurs
	Player();
	Player(float x, float y);
	Player(sf::Vector2f pos, float w, float h);
	Player(sf::Vector2f pos, float w, float h, sf::Vector2f speed, int weight, std::shared_ptr<Animation> anim);
	void jump();
#pragma endregion

#pragma region methodes

	void hit(unsigned int hp);
	//void update(float elapsedTime);
	void triggerJump();
	void doCrouch();
	void doJump();
	void crouch();
#pragma region set()
	void setHealth(int h);
	void setVerticalSpeed(float v);
#pragma endregion

#pragma region get()
	int getHealth();
	float getVerticalSpeed();
	bool isJumping();
	bool isCrouching();
#pragma endregion

#pragma endregion

	~Player();
private:
	void init();
	void createAnimation();


	int unsigned m_health;
	int m_jumpHeight;
	sf::Vector2f m_rollPosition;

	bool m_jumping;
	bool m_crouching;
	JumpState m_currentJumpState;
};
