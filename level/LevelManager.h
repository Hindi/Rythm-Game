#pragma once

#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../utility/EventManager.hpp"

/**
 * @struct	Spawn
 *
 * @brief	Struct spawn that hold the datas for each obstacle.
 *
 * @author	Vincent
 * @date	16/06/2014
 */

struct Spawn {
	std::string obs;
	float time;
	std::string sound;
};

/**
 * @class	LevelManager
 *
 * @brief	Get the info about the level from a file, then give the necessary informations
 * 			to spawn obstacles when the levelBuilder asks for them.
 *
 * @author	Vincent
 * @date	16/06/2014
 */
class LevelManager
{
public:
	LevelManager();
	~LevelManager();
	Spawn getNextObstacle();
	void reset();
	void parseLevel(std::string name);

private:

	float m_acceleration;
	size_t m_obstacleNumber;
	std::vector < Spawn > m_spawnList;
};

