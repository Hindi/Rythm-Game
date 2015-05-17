#include "GameState.h"

/**
 * @fn	GameState::GameState(GameStateManager& gameStateManager)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	gameStateManager	a reference to the GameStateManager, used in derived class to 
 * 										change the game states.
 */
GameState::GameState(GameStateManager& gameStateManager) :
m_gameStateManager(gameStateManager)
{

}