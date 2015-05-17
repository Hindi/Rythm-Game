#include "LevelManager.h"

/**
 * @fn	LevelManager::LevelManager()
 *
 * @brief	Default constructor.
 *
 */
LevelManager::LevelManager()
{
	m_obstacleNumber = 0;
	m_acceleration = 0.9f;
	EventManager<void>::getInstance().addListener("death", std::bind(&LevelManager::reset, this));
}

/**
 * @fn	LevelManager::~LevelManager()
 *
 * @brief	Destructor.
 *
 */
LevelManager::~LevelManager()
{
}

/**
 * @fn	void LevelManager::parseLevel()
 *
 * @brief	Parse a file to generate the level.
 *
 */
void LevelManager::parseLevel(std::string name)
{
	m_spawnList.clear();
	std::ifstream file("../JIN4/level/" + name + ".txt");
	std::string line;
	assert(file.is_open() == true);
	while (std::getline(file, line))
	{
		Spawn spawn;
		std::stringstream ss(line);
		//Parse l'obstacle, le temps et le son  à jouer pour chaque obstacle
		std::getline(ss, spawn.obs, ' ');
		std::string ltime;
		std::getline(ss, ltime, ' ');
		spawn.time = (float)atof(ltime.c_str());

		std::getline(ss, spawn.sound, ' ');
		
		if (spawn.sound == "kick")
			spawn.sound = "Kick 001.wav";
		if (spawn.sound == "snare")
			spawn.sound = "Snare 001.wav";
		else
		{
			spawn.sound += ".wav";
		}

		m_spawnList.push_back(spawn);
	}

	file.close();
}

/**
 * @fn	std::pair<std::string, float> LevelManager::getNextObstacle()
 *
 * @brief	Gets the next obstacle to be spawned.
 *
 * @return	The next obstacle.
 */
Spawn LevelManager::getNextObstacle()
{
	Spawn obs = m_spawnList[m_obstacleNumber];
	if (m_obstacleNumber < m_spawnList.size() - 1)
		m_obstacleNumber++;
	else
	{
		m_obstacleNumber = 0;
		m_acceleration *= 0.9f;
	}
	obs.time *= m_acceleration;
	return obs;
}

/**
 * @fn	void LevelManager::reset()
 *
 * @brief	Resets this object when the player lose.
 */
void LevelManager::reset()
{
	m_spawnList.clear();
	m_acceleration = 1;
	m_obstacleNumber = 0;
}