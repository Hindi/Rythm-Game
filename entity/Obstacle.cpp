#include"Obstacle.h"

/**
 * @fn	Obstacle::Obstacle()
 *
 * @brief	Default constructor.
 *
 */
Obstacle::Obstacle()
{

}

/**
 * @fn	Obstacle::Obstacle(TypeObstacle TO)
 *
 * @brief	Constructor.
 *
 *
 * @param	TO	the obstacle type.
 *
 */
Obstacle::Obstacle(TypeObstacle TO)
{	
	m_animation = std::shared_ptr<Animation>(new Animation(100, false, false, 0.05f));
	switch (TO)
	{
	case (TypeObstacle::JUMP) :
	{
			triggerSegment.first = 75;
			triggerSegment.second = 280;
			setBox(800, 450, 50, 50);
			//m_triggerBox();
			inUse = false;
			sf::Image m_image(MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/ObstacleJump.png"));
			auto jumpObstacleAnim = std::make_shared<Anim>("jump");
			jumpObstacleAnim->pushFrame(Frame(m_image, sf::Rect<int>(0,0,50,50)));
			m_animation->addAnim("jump", jumpObstacleAnim);
			m_animation->setAnim("jump", true);
			AnimationManager::getInstance().addAnimation(m_animation);
			break;
		}
	case (TypeObstacle::CROUCH) :
		{	
			triggerSegment.first = 0;
			triggerSegment.second =350;
			setBox(800, 60, 35, 400);
			inUse = false;
			sf::Image m_image(MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/crouchObstacle.png"));
			auto jumpObstacleAnim = std::make_shared<Anim>("crouch");
			jumpObstacleAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, 35, 400)));
			m_animation->addAnim("crouch", jumpObstacleAnim);
			m_animation->setAnim("crouch", true);
			AnimationManager::getInstance().addAnimation(m_animation);
			break;
		}

	default:
		{
			std::cout << "DEBUG : Ce type d'obstacle n'éxiste pas";
			break;
		}
	}
}

/**
 * @fn	void Obstacle::setActive(bool b)
 *
 * @brief	Sets the obstacle as active (when used for collisions and drew). This methods exists because
 * 			the obstacleManager uses object pulling.
 *
 *
 * @param	b	true to b.
 */
void Obstacle::setActive(bool b)
{
	inUse = b;
	m_animation->setDrawable(b);
	if(!b)
	{
		m_speed = sf::Vector2f(0, 0);
		moveTo(sf::Vector2f(800, getPosition().y));
	}
}

/**
 * @fn	bool Obstacle::isActive()
 *
 * @brief	Query if this object is active.
 *
 * @return	true if active, false if not.
 */
bool Obstacle::isActive()
{
	return inUse;
}

/**
 * @fn	void Obstacle::createAnimation()
 *
 * @brief	Creates the animation.
 *
 */
void Obstacle::createAnimation()
{

}


/**
 * @fn	Obstacle::~Obstacle()
 *
 * @brief	Destructor.
 *
 */
Obstacle::~Obstacle()
{

}

/**
 * @fn	bool Obstacle::boxInTrigger(sf::Rect<float> theBox)
 *
 * @brief	Checks if the box in parameter intersects the trigger. Used to play a sound when the 
 * 			player jumps and is in the trigger's area.
 *
 * @param	theBox	the box.
 *
 * @return	true if it succeeds, false if it fails.
 */
bool Obstacle::boxInTrigger(sf::Rect<float> theBox)
{	
	//std::cout << theBox.left << " " << m_box.left - triggerSegment.first << " " << m_box.left + m_box.width - triggerSegment.second << std::endl;
	if (theBox.left < m_box.left - triggerSegment.first && theBox.left > m_box.left + m_box.width - triggerSegment.second)
	{
		return true;
	}
	return false;
}

/**
 * @fn	void setSoundName(std::string soundName)
 *
 * @brief	Sets sound name.
 *
 * @param	soundName	Name of the sound.
 */
void Obstacle::setSoundName(std::string soundName)
{
	m_soundName = soundName;
}

/**
 * @fn	std::string getSoundName()
 *
 * @brief	Gets sound name.
 *
 *
 *@return	The sound name.
 */
std::string Obstacle::getSoundName()
{
	return m_soundName;
}