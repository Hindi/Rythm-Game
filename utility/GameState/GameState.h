#pragma once

#include "../../entity/Player.h"

/**
 * @class	GameStateManager
 *
 * @brief	Interface for the game states.
 *
 * @author	Vincent
 * @date	09/06/2014
 */

class GameStateManager;

class GameState
{
public:

	/**
	 * @fn	GameState::GameState(GameStateManager& gameStateManager);
	 *
	 * @brief	Constructor.
	 *
	 * @param [in,out]	gameStateManager	Manager for game state.
	 */
	GameState(GameStateManager& gameStateManager);

	/**
	 * @fn	virtual void GameState::start() = 0;
	 *
	 * @brief	Function called when the state starts.
	 */
	virtual void start() = 0;

	/**
	 * @fn	virtual void GameState::end() = 0;
	 *
	 * @brief	unction called when the state ends.
	 *
	 */
	virtual void end() = 0;

	/**
	 * @fn	virtual void GameState::inputKeyReturn() = 0;
	 *
	 * @brief	Called by the inputManager for return key event
	 *
	 */
	virtual void inputKeyReturn() = 0;

	/**
	* @fn	virtual void GameState::inputKeyEscape() = 0;
	*
	* @brief	Called by the inputManager for escape key event
	*
	*/
	virtual void inputKeyEscape() = 0;

	/**
	* @fn	virtual void GameState::inputKeyUp() = 0;
	*
	* @brief	Called by the inputManager for up key event
	*
	*/
	virtual void inputKeyUp() = 0;

	/**
	* @fn	virtual void GameState::inputKeyDown() = 0;
	*
	* @brief	Called by the inputManager for down key event
	*
	*/
	virtual void inputKeyDown() = 0;

protected:
	GameStateManager& m_gameStateManager;
};
