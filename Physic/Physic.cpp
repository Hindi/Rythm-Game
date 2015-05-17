#include "Physic.h"

/**
* @fn	Physic(LevelBuilder &levelBuilder, Player &player)
*
* @brief	Constructor
*/

Physic::Physic(LevelBuilder &levelBuilder, Player &player) :
m_levelBuilder(levelBuilder),
m_player(player)
{
	EventManager<void>::getInstance().addListener("inAction", std::bind(&Physic::triggersound, this));
	EventManager<bool>::getInstance().addListener("freeze", std::bind(&Physic::triggerFreeze, this, std::placeholders::_1));
	EventManager<void>::getInstance().addListener("debug", std::bind(&Physic::triggerdebug, this));
	m_freezed = true;
	m_debug = false;
}

/**
 * @fn	Physic::~Physic()
 *
 * @brief	Destructor.
 *
 */
Physic::~Physic()
{
}


/**
*
* @fn	triggerdebug()*
*
* @brief	active the debug mode
*
*
*/

void Physic::triggerdebug()
{
	m_debug = true;
}

/**
* @fn	void  Physic::computePhysic()
*
* @brief	Compute the displacement of each entity in the game.
*
*/

void Physic::computePhysic()
{	
	float deltaTime = m_clock.getElapsedTime().asSeconds();
	if (!m_freezed)
	{
		auto obstacles = m_levelBuilder.getObstacles();
		//First of all we move the obstacle and disable them if needed
#pragma region Move Obstacle
		bool needToClear= false;
		if (obstacles.size() > 0)
		{
			for (auto obs : obstacles)
			{
				obs->translate(sf::Vector2f(obs->getSpeed().x * deltaTime * speed_factor, 0));
				if (obs->getPosition().x + (obs->getWidth()) < 0)
				{	
					obs->setActive(false);
					needToClear = true;
				}
			}
		}
		if (needToClear)
		{
			EventManager<void>::getInstance().call("clearFirstObs");
		}



#pragma endregion

		// then we move the player
#pragma region MovePlayer

	if (m_player.isJumping())
	{
		m_player.doJump();
		m_player.translate(sf::Vector2f(0, m_player.getSpeed().y * deltaTime * speed_factor));
	}

		if (m_player.isCrouching())
		{
			m_player.doCrouch();
		}
#pragma endregion

		// then we check collision
#pragma region Check Collision
		// if no plateform, jump is piloted by player::jump() 
		{
			if (obstacles.size() >0)
			{
				if (obstacles.front()->getBox().intersects(m_player.getBox()))
				{
					EventManager<void>::getInstance().call("death");
					

				}
			}
		}

		if (m_debug)
			for (auto obs : obstacles)
				if (obs->boxInTrigger(m_player.getBox()))
				{
					if (obs->getHeight() < 100)
						m_player.jump();
					else
						m_player.crouch();
				}
	}
	m_clock.restart();
}


/*
* @fn	void  Physic::triggersound()
*
* @brief	Check if the player is in the triggerSegment when he jump and so if we need to play the sound or not
*
*/

void Physic::triggersound()
{
	auto obstacles = m_levelBuilder.getObstacles();
	for (auto obs : obstacles)
		if (obs->boxInTrigger(m_player.getBox()))
		{
			EventManager<std::string>::getInstance().call("sucessfullJump", obs->getSoundName());
			//std::cout << "playsound " << std::endl;
		}
}

/*
*
* @fn	void  Physic::triggerFreeze()
*
* @brief	Set the boolean m_freezed to b the param.
*
* @param bool b;
*/


void Physic::triggerFreeze(bool b)
{
	m_freezed = b;
}