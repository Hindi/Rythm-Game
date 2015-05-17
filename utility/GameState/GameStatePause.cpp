#include "GameStatePause.h"

/**
 * @fn	GameStatePause::GameStatePause(GameStateManager& gameStateManager, Player &player)
 *
 * @brief	Constructor.
 * 			
 * @param [in,out]	gameStateManager	Manager for game state.
 * @param [in,out]	player				The player.
 */

GameStatePause::GameStatePause(GameStateManager& gameStateManager, UInterface &interface) :
GameState(gameStateManager),
m_interface(interface)
{
}

/**
 * @fn	GameStatePause::~GameStatePause()
 *
 * @brief	Destructor.
 *
 */
GameStatePause::~GameStatePause()
{

}

/**
 * @fn	void GameStatePause::start()
 *
 * @brief	Trigger the event "pause" with true parameter (starting the pause).
 *
 */

void GameStatePause::start()
{
	m_interface.triggerPause(true);
	EventManager<bool>::getInstance().call("freeze", true);
}

void GameStatePause::end()
{
	m_interface.triggerPause(false);
}

/**
 * @fn	void GameStatePause::inputKeyReturn()
 *
 * @brief	Change state to GameStateGame
 *
 */
void GameStatePause::inputKeyReturn()
{
	m_gameStateManager.changeState("game");
}

/**
* @fn	void GameStatePause::inputKeyEscape()
*
* @brief	Change state to GameStateGame
*
*/
void GameStatePause::inputKeyEscape()
{
	m_gameStateManager.changeState("game");
}

/**
 * @fn	void GameStatePause::inputKeyUp()
 *
 * @brief	Input key up.
 *
 */
void GameStatePause::inputKeyUp()
{
}

/**
 * @fn	void GameStatePause::inputKeyDown()
 *
 * @brief	Input key down.
 *
 */
void GameStatePause::inputKeyDown()
{
}