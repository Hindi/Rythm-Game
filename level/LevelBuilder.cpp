#include "LevelBuilder.h"

/**
 * @fn	LevelBuilder::LevelBuilder(LevelManager &levelManager)
 *
 * @brief	Constructor.
 *
 */
LevelBuilder::LevelBuilder(LevelManager &levelManager):
m_levelManager(levelManager)
{
	m_timeBeforeObstacle = 0;
	m_freezed = true;
	m_debug = false;

	// on rajoute le sol et le plafond

	sf::Image m_image(MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/bord.png"));
	auto  m_animation = std::shared_ptr<Animation>(new Animation(150, false, false, 0.05f));
	auto ground = std::make_shared<Anim>("ground");
	ground->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, 800, 600)));
	m_animation->addAnim("ground", ground);
	m_animation->setAnim("ground", true);
	AnimationManager::getInstance().addAnimation(m_animation);

	EventManager<bool>::getInstance().addListener("freeze", std::bind(&LevelBuilder::triggerFreeze, &(*this), std::placeholders::_1));
	EventManager<void>::getInstance().addListener("clearFirstObs", std::bind(&LevelBuilder::clearFirstObs, &(*this)));
	EventManager<void>::getInstance().addListener("death", std::bind(&LevelBuilder::reset, this));
	EventManager<void>::getInstance().addListener("debug", std::bind(&LevelBuilder::triggerdebug, this));
}

void LevelBuilder::triggerdebug()
{
	m_debug = true;
}

/**
 * @fn	LevelBuilder::~LevelBuilder()
 *
 * @brief	Destructor.
 *
 */
LevelBuilder::~LevelBuilder()
{

}

/**
 * @fn	void LevelBuilder::clearFirstObs()
 *
 * @brief	pop the first obstacle (when it reaches the left side of the screen)
 *
 */
void LevelBuilder::clearFirstObs()
{	
	m_obstacles.pop_front();
}

/**
 * @fn	void LevelBuilder::triggerPause(bool pause)
 *
 * @brief	Trigger pause. If true save current clock time, if false reset clock.
 *
 * @param	pause	true to pause.
 */
void LevelBuilder::triggerFreeze(bool freeze)
{
	m_freezed = freeze;
	if (freeze)
		m_saveTime = m_clock.getElapsedTime().asSeconds();//On sauvegarde le temps avant de se mettre en pause
	else
		m_clock.restart();//On remet l'horloge à zéro après la pause
}

/**
 * @fn	void LevelBuilder::update()
 *
 * @brief	If it's time to send an obstacle, call spawn(). Called each frame.
 * 			
 */
void LevelBuilder::update()
{
	if (!m_freezed)
		if (timeToSpawn())
			spawn();
}

/**
 * @fn	bool LevelBuilder::timeToSpawn()
 *
 * @brief	Check if the next obstacle needs to be sent. Use m_savedTime in case of a pause being triggered
 *
 * @return	true if it succeeds, false if it fails.
 */

bool LevelBuilder::timeToSpawn()
{
	
	return (m_timeBeforeObstacle < m_clock.getElapsedTime().asMilliseconds() + m_saveTime);
}

/**
 * @fn	void LevelBuilder::spawn()
 *
 * @brief	Query the ObstacleManager for a new obstacle and query the LevelManager for the next obstacle and time.
 *
 */
void LevelBuilder::spawn()
{
	if (m_debug)
	{
		static int i{ 0 };
		i++;
		std::cout << i << std::endl;
	}
	m_clock.restart();
	m_saveTime = 0;
	Spawn summon = m_levelManager.getNextObstacle();
	m_timeBeforeObstacle = summon.time;

	TypeObstacle obs{ TypeObstacle::JUMP };
	if (summon.obs == "jump")
		obs = TypeObstacle::JUMP;
	else if ((summon.obs == "crouch"))
		obs = TypeObstacle::CROUCH;
	else
		std::cout << "DEBUG : LevelBuilder | Type d'obstacle inconnu : " << summon.obs << std::endl;
	m_obstacles.push_back(ObstacleManager::getInstance().getObstacle(obs, summon.sound));
}

/**
 * @fn	std::list<std::shared_ptr<Obstacle>> & LevelBuilder::getObstacles()
 *
 * @brief	Gets the obstacles.
 *
 * @return	The obstacles.
 */
std::list<std::shared_ptr<Obstacle>> & LevelBuilder::getObstacles()
{
	return m_obstacles;
}

/**
 * @fn	void LevelBuilder::reset()
 *
 * @brief	Resets this object when the player lose.
 *
 */
void LevelBuilder::reset()
{
	for (auto obs : m_obstacles)
	{
		obs->setActive(false);
	}
	m_obstacles.clear();
	m_clock.restart();
}