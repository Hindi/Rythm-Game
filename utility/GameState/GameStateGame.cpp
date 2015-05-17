#include "GameStateGame.h"

/**
 * @fn	GameStateGame::GameStateGame(GameStateManager& gameStateManager, Player &player)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	gameStateManager	Manager for game state.
 * @param [in,out]	player				The player.
 */

GameStateGame::GameStateGame(GameStateManager& gameStateManager, Player &player) :
GameState(gameStateManager),
m_player(player)
{
	EventManager<void>::getInstance().addListener("death", std::bind(&GameStateGame::triggerDeath, this));
}

/**
 * @fn	GameStateGame::~GameStateGame()
 *
 * @brief	Destructor.
 *
 */
GameStateGame::~GameStateGame()
{
}

/**
 * @fn	void GameStateGame::start()
 *
 * @brief	Trigger an event "pause" with parameter false (leaving the pause).
 *
 */
void GameStateGame::start()
{
	EventManager<bool>::getInstance().call("freeze", false);
}

void GameStateGame::end()
{

}

void GameStateGame::inputKeyReturn()
{

}

/**
 * @fn	void GameStateGame::inputKeyEscape()
 *
 * @brief	Call a changeState to GameStatedPause
 *
 */
void GameStateGame::inputKeyEscape()
{
	m_gameStateManager.changeState("pause");
}

/**
 * @fn	void GameStateGame::inputKeyUp()
 *
 * @brief	The player jumps.
 */
void GameStateGame::inputKeyUp()
{
	m_player.jump();
}

/**
 * @fn	void GameStateGame::inputKeyDown()
 *
 * @brief	The player crouch.
 *
 */
void GameStateGame::inputKeyDown()
{
	m_player.crouch();
}

void GameStateGame::triggerDeath()
{
	m_gameStateManager.changeState("end");
}