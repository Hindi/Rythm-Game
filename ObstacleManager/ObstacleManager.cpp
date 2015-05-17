#include "ObstacleManager.h"

/**
* @fn	ObstacleManager::ObstacleManager()
*
* @brief	Constructor
*
*/
ObstacleManager::ObstacleManager()
{
}

/**
 * @fn	ObstacleManager::~ObstacleManager()
 *
 * @brief	Destructor.
 *
 */
ObstacleManager::~ObstacleManager()
{

}

/**
* @fn	std::shared_ptr<Obstacle> ObstacleManager::getObstacle(TypeObstacle to, std::string soundName)
*
* @brief	Check in the map if they're is a vector of the ased type of obstacle and create one if needed then call getObstacleInVector.
*
* @param	to	 The obtacle type
* @param	soundName the sound that the obstacle need to play
* 
* @return A shared pointer on a available obstacle 
*/

std::shared_ptr<Obstacle> ObstacleManager::getObstacle(TypeObstacle to, std::string soundName)
{	
	if (m_obstacles.find(to) != m_obstacles.end())
		return getObstacleInVector(m_obstacles[to], to, soundName);
	
	std::vector<std::shared_ptr<Obstacle>> m_vector;
	m_obstacles[to] = m_vector;
	return getObstacleInVector(m_vector, to, soundName);
}

/**
* @fn	std::shared_ptr<Obstacle> ObstacleManager::getObstacleInVector(std::vector<std::shared_ptr<Obstacle>> & m_vector, TypeObstacle to, std::string soundName)
*
* @brief	Check in the vector if they're is an obstacle who is not in use in the vector and create one if needed.Also affect the variable soundName with the rigght sound to play.
*
* @param	m_vector	the reference of the vector in which we need to check
* @param	to	 The obtacle type
* @param	soundName	the sound that the obstacle need to play
*
* @return A shared pointer on a available obstacle
*/

std::shared_ptr<Obstacle> ObstacleManager::getObstacleInVector(std::vector<std::shared_ptr<Obstacle>> & m_vector, TypeObstacle & to, std::string soundName)
{
	for (auto Obs : m_vector)
	{
		if (!Obs->isActive())
		{	
			Obs->setSpeed(sf::Vector2f(-25, 0));
			Obs->setActive(true);
			Obs->setSoundName(soundName);
			return Obs;
		}
	}
	std::shared_ptr<Obstacle> m_shrptr(new Obstacle(to));
	m_shrptr->setActive(true);
	m_shrptr->setSpeed(sf::Vector2f(-25, 0));
	m_vector.push_back(m_shrptr);
	m_shrptr->setSoundName(soundName);

	return m_shrptr;
}

/**
* @fn	void  Physic::getInsance()
*
* @brief	return the singleton of the class
*
*/

ObstacleManager& ObstacleManager::getInstance()
{
	static ObstacleManager manager;
	return manager;
}


int	ObstacleManager::getMapSize()
{
	return m_obstacles.size();
}
int ObstacleManager::getVectorSize(TypeObstacle to)
{
	return m_obstacles[to].size() + 1;
}
std::shared_ptr<Obstacle> ObstacleManager::getVectorFirstElement(TypeObstacle to)
{
	return  m_obstacles[to][0];
}