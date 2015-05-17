#pragma once

#include "LevelManager.h"
#include "../entity/TypeObstacle.h"
#include "../ObstacleManager/ObstacleManager.h"
#include "../utility/EventManager.hpp"
#include <list>
#include <SFML/Graphics.hpp>

/**
 * @class	LevelBuilder
 *
 * @brief	Query the LevelManager for the informations about the current level and spawn the obstacles when it's time.
 *
 * @author	Vincent
 * @date	16/06/2014
 */

class LevelBuilder
{
public:
	LevelBuilder(LevelManager &levelManager);
	~LevelBuilder();

	void update();
	void triggerFreeze(bool pause);
	void clearFirstObs();
	std::list<std::shared_ptr<Obstacle>> & getObstacles();
	void reset();
	void triggerPlay();
	void triggerdebug();

private:
	bool timeToSpawn();
	void spawn();

	bool m_playing;
	LevelManager &m_levelManager;
	sf::Clock m_clock;
	float m_timeBeforeObstacle;
	float m_saveTime;
	bool m_freezed;
	bool m_debug;
	std::list<std::shared_ptr<Obstacle>> m_obstacles;
	
};

