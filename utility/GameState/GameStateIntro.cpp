#include "GameStateIntro.h"

/**
 * @fn	GameStateIntro::GameStateIntro(GameStateManager& gameStateManager, Player &player)
 *
 * @brief	Constructor.
 *
 *
 * @param [in,out]	gameStateManager	Manager for game state.
 * @param [in,out]	player				The player.
 */

GameStateIntro::GameStateIntro(GameStateManager& gameStateManager, UInterface &interface) :
GameState(gameStateManager),
m_interface(interface)
{
	EventManager<void>::getInstance().addListener("play", std::bind(&GameStateIntro::triggerPlay, this));
}

/**
 * @fn	void GameStateIntro::triggerPlay()
 *
 * @brief	Trigger play.
 *
 */
void GameStateIntro::triggerPlay()
{
	m_gameStateManager.changeState("game");
	EventManager<bool>::getInstance().call("freeze", false);
}

/**
 * @fn	GameStateIntro::~GameStateIntro()
 *
 * @brief	Destructor.
 *
 */
GameStateIntro::~GameStateIntro()
{
}

/**
 * @fn	void GameStateIntro::start()
 *
 * @brief	Trigger the event "pause" with true parameter (starting the pause).
 *
 */
void GameStateIntro::start()
{
	m_interface.triggerIntro(true);
	EventManager<bool>::getInstance().call("freeze", true);
}

/**
 * @fn	void GameStateIntro::end()
 *
 * @brief	Ends this object.
 *
 */
void GameStateIntro::end()
{
	m_interface.triggerIntro(false);
}

/**
 * @fn	void GameStateIntro::inputKeyReturn()
 *
 * @brief	Change state to GameStateGame.
 *
 */
void GameStateIntro::inputKeyReturn()
{
	m_interface.startLevel();
}

/**
 * @fn	void GameStateIntro::inputKeyEscape()
 *
 * @brief	Input key escape.
 *
 */
void GameStateIntro::inputKeyEscape()
{

}

/**
 * @fn	void GameStateIntro::inputKeyUp()
 *
 * @brief	Input key up.
 *
 */
void GameStateIntro::inputKeyUp()
{
	m_interface.decrementLevelSelect();
}

/**
 * @fn	void GameStateIntro::inputKeyDown()
 *
 * @brief	Input key down.
 *
 */
void GameStateIntro::inputKeyDown()
{
	m_interface.incrementLevelSelect();
}