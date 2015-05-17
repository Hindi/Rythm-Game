#pragma once
#include "Entity.h"
#include "TypeObstacle.h"
#include "..\media\sons\SoundManager.h"
#include "..\media\animations\AnimationManager.h"

/**
* @class	Entity
*
* @brief	 Obstacle class, object can be killer obstacle, or just a platform the player can touch
*
* @author	Quentin
* @date	09/06/2014
*/

class Obstacle : public Entity
{
public : 
	Obstacle();
	Obstacle(TypeObstacle to);
	void setActive(bool b);
	bool isActive();
	bool getKill();
	bool boxInTrigger(sf::Rect<float> theBox);
	~Obstacle();
	void setSoundName(std::string soundName);
	std::string getSoundName();

protected :

	void createAnimation();
	std::pair<float, float> triggerSegment;
	bool inUse;
	std::string m_soundName;
};