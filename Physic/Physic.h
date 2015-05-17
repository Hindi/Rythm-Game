#pragma once
#include <list>
#include "..\entity\Player.h"
#include "..\entity\Obstacle.h"
#include "../level/LevelBuilder.h"

/**
* @class	Physic
*
* @brief	Class which computes physics stuffs
*
* @author	Quentin
* @date	09/06/2014
*/

class Physic
{
public:
	Physic(LevelBuilder &levelBuilder, Player &player);
	~Physic();
	void computePhysic();
	void triggersound();
	void triggerdebug();
	void triggerFreeze(bool b);

private:
	static const int speed_factor = 50;
	LevelBuilder &m_levelBuilder;
	Player &m_player;
	sf::Clock m_clock;
	bool m_freezed;
	bool m_debug;
};

