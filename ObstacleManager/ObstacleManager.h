#pragma once
#include "../entity/Obstacle.h"
#include "../entity/TypeObstacle.h"

/**
* @class	ObstacleManager
*
* @brief	Class for the pooling of the obstacle. it is use also as a factory as it create new obstacle if needed
*
* @author	Quentin
* @date	09/06/2014
*/

class ObstacleManager
{
public:
	static ObstacleManager& getInstance();
	~ObstacleManager();
	std::shared_ptr<Obstacle> getObstacle(TypeObstacle to, std::string soundName);
	int	getMapSize();
	int getVectorSize(TypeObstacle to);
	std::shared_ptr<Obstacle> getVectorFirstElement(TypeObstacle to);

	//void reset();

private:
	ObstacleManager();
	std::map<TypeObstacle, std::vector<std::shared_ptr<Obstacle>>> m_obstacles;
	std::shared_ptr<Obstacle> getObstacleInVector(std::vector<std::shared_ptr<Obstacle>> & m_vector, TypeObstacle & to, std::string soundName);
};

