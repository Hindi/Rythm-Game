#include "GameStateEndGame.h"

/**
 * @fn	GameStateEndGame::GameStateEndGame(GameStateManager& gameStateManager, Player &player)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	gameStateManager	Manager for game state.
 * @param [in,out]	player				The player.
 */

GameStateEndGame::GameStateEndGame(GameStateManager& gameStateManager, UInterface &interface) :
GameState(gameStateManager),
m_interface(interface)
{
}

/**
 * @fn	GameStateEndGame::~GameStateEndGame()
 *
 * @brief	Destructor.
 *
 */
GameStateEndGame::~GameStateEndGame()
{
}

/**
* @fn	void GameStateEndGame::start()
*
* @brief	Trigger an event "pause" with parameter true.
*
*/
void GameStateEndGame::start()
{
	m_interface.triggerLost(true);
	EventManager<bool>::getInstance().call("freeze", true);
}

/**
* @fn	void GameStateEndGame::end()
*
* @brief	Trigger an event "pause" with parameter true.
*
*/
void GameStateEndGame::end()
{
	m_interface.triggerLost(false);
}

void GameStateEndGame::inputKeyReturn()
{
	m_gameStateManager.changeState("intro");
}

/**
* @fn	void GameStateEndGame::inputKeyEscape()
*
* @brief	Call a changeState to GameStateGame
*
*/
void GameStateEndGame::inputKeyEscape()
{
	m_gameStateManager.changeState("intro");
}

/**
* @fn	void GameStateEndGame::inputKeyUp()
*
* @brief	Nothing happens.
*/
void GameStateEndGame::inputKeyUp()
{

}

/**
* @fn	void GameStateEndGame::inputKeyDown()
*
* @brief	Nothing happens.
*
*/
void GameStateEndGame::inputKeyDown()
{

}