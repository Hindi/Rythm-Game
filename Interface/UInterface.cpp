#include "UInterface.h"

/**
 * @fn	UInterface::UInterface()
 *
 * @brief	Default constructor. Add listeners for events and create the menus
 *
 */
UInterface::UInterface(LevelManager& levelManager):
m_levelManager(levelManager)
{
	m_levelSelect = 0;
	m_scoreCount = 0;

	//events
	EventManager<void>::getInstance().addListener("play", std::bind(&UInterface::triggerPlay, this));
	EventManager<std::string >::getInstance().addListener("sucessfullJump", std::bind(&UInterface::triggerScore, this));

	//Texte
	
	if (!m_font.loadFromFile("../JIN4/media/font/BlackoakStd.otf"))
	{
		std::cout << "DEBUG :UInterface | Failed to load font" << std::endl;
	}

	if (!m_font2.loadFromFile("../JIN4/media/font/digital-7.ttf"))
	{
		std::cout << "DEBUG :UInterface | Failed to load font" << std::endl;
	}

	sf::Image select_image = MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/selecteur.png");
	
	animationSelecteur = std::shared_ptr<Animation>(new Animation(100, false, false, 0.05f));


	auto selecteurAnim = std::make_shared<Anim>("selec");
	selecteurAnim->pushFrame(Frame(select_image, sf::Rect<int>(0, 0, 50, 50)));
	animationSelecteur ->addAnim("selec", selecteurAnim);
	animationSelecteur->setAnim("selec", true);
	animationSelecteur->setDrawable(false);
	animationSelecteur->setPosition(sf::Vector2f(170, 250));
	animationSelecteur->scale(sf::Vector2f(0.4, 0.24));
	AnimationManager::getInstance().addAnimation(animationSelecteur);

	m_pauseMenu = createLayer("PAUSE", sf::Color(200, 56, 56, 255), 60, sf::Vector2f(150, 150));
	m_loseMenu = createLayer("YOU LOSE", sf::Color(200, 56, 56, 255), 60, sf::Vector2f(0, 150));
	m_input = createLayer("UP arrow : jump \nDOWN arrow : crouch", sf::Color(200, 56, 56, 255), 15, sf::Vector2f(10, 550));
	m_Score = createLayer(std::to_string(m_scoreCount), sf::Color(200, 56, 56, 255), 50, sf::Vector2f(370, 30));
	m_Score.m_text.setFont(m_font2);

	m_levelList.push_back(createLayer("Tetris", sf::Color(200, 56, 56, 255), 20, sf::Vector2f(0, 0)));
	m_levelList.push_back(createLayer("Leva's Polka", sf::Color(200, 56, 56, 255), 20, sf::Vector2f(0, 0)));
	m_levelList.push_back(createLayer("Hymne à la joie", sf::Color(200, 56, 56, 255), 20, sf::Vector2f(0, 0)));

	updateLevelListPosition();
	triggerIntro(true);
}

/**
 * @fn	void UInterface::startLevel()
 *
 * @brief	Asks the LevelManager to parse the selected level then trigger the "play" event.
 *
 */
void UInterface::startLevel()
{
	m_levelManager.parseLevel(m_levelList[m_levelSelect].m_text.getString());
	EventManager<void>::getInstance().call("play");
}

/**
 * @fn	void UInterface::updateLevelListPosition()
 *
 * @brief	Move the name of the level when the player changes its selection.
 *
 */
void UInterface::updateLevelListPosition()
{
	for (int i{ 0 }; i < m_levelList.size(); ++i)
		m_levelList[i].m_text.setPosition(sf::Vector2f(200, 250 + (i - m_levelSelect) * 20));
}

/**
 * @fn	Layer UInterface::createLayer(std::string text, sf::Color color, int size, sf::Vector2f position)
 *
 * @brief	Creates a layer made out of an sf::text.
 *
 * @param	text		The text.
 * @param	color   	The color.
 * @param	size		The size.
 * @param	position	The position.
 *
 * @return	The new layer.
 */
Layer UInterface::createLayer(std::string text, sf::Color color, int size, sf::Vector2f position)
{
	Layer layer;
	layer.m_text.setFont(m_font);
	layer.m_text.setString(text);
	layer.m_text.setColor(color);
	layer.m_text.setCharacterSize(size);
	layer.m_text.setPosition(position);
	layer.drawable = false;
	return layer;
}

/**
 * @fn	UInterface::~UInterface()
 *
 * @brief	Destructor.
 *
 */
UInterface::~UInterface()
{

}

/**
 * @fn	void UInterface::triggerPause(bool pause)
 *
 * @brief	Trigger pause, called by the EventManager
 *
 * @param	pause	true to pause.
 */
void UInterface::triggerPause(bool pause)
{
	m_pauseMenu.drawable = pause;
}

/**
 * @fn	void UInterface::triggerLost()
 *
 * @brief	Trigger lost state.
 *
 */
void UInterface::triggerLost(bool lose)
{
	m_loseMenu.drawable = lose;
}

/**
 * @fn	void UInterface::triggerPlay()
 *
 * @brief	Trigger play state.
 *
 */
void UInterface::triggerPlay()
{
	m_pauseMenu.drawable = false;
	m_loseMenu.drawable = false;
	m_Score.drawable = true;
	m_scoreCount = 0;
	m_Score.m_text.setString(std::to_string(m_scoreCount));
}

/**
 * @fn	void UInterface::triggerIntro()
 *
 * @brief	Trigger intro state.
 *
 */
void UInterface::triggerIntro(bool intro)
{
	for (auto &it : m_levelList)
		it.drawable = intro;
	m_input.drawable = intro;
	if (intro)
		animationSelecteur->setDrawable(true);
	else
		animationSelecteur->setDrawable(false);
}

/**
 * @fn	void UInterface::triggerScore()
 *
 * @brief	Increment the score on trigger.
 *
 */
void UInterface::triggerScore()
{
	m_scoreCount += 1;
	m_Score.m_text.setString(std::to_string(m_scoreCount));
}

/**
 * @fn	void UInterface::update()
 *
 * @brief	Updates the distance and draw it.
 *
 */
void UInterface::update(sf::RenderWindow& window)
{
	for (auto &it : m_levelList)
		it.draw(window);
	m_pauseMenu.draw(window);
	m_loseMenu.draw(window);
	m_Score.draw(window);
	m_input.draw(window);
}

/**
 * @fn	void UInterface::incrementLevelSelect()
 *
 * @brief	Used on level selection in the menu.
 *
 */
void UInterface::incrementLevelSelect()
{
	if (m_levelSelect < m_levelList.size() -1)
	{
		m_levelSelect++;
		updateLevelListPosition();
	}
}

/**
* @fn	void UInterface::decrementLevelSelect()
*
* @brief	Used on level selection in the menu.
*
*/
void UInterface::decrementLevelSelect()
{
	if (m_levelSelect > 0)
	{
		m_levelSelect--;
		updateLevelListPosition();
	}
}