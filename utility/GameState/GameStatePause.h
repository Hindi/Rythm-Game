#pragma once

#include <memory>

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateGame.h"
#include "../../Interface/UInterface.h"

	/**
	 * @class	GameStatePause
	 *
	 * @brief	State when the player pause the game.
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 */

class GameStatePause : public GameState
{
public:
	GameStatePause(GameStateManager& gameStateManager, UInterface &interface);
	virtual ~GameStatePause();

	virtual void start();
	virtual void end();
	void inputKeyReturn();
	void inputKeyEscape();
	void inputKeyUp();
	void inputKeyDown();
	UInterface &m_interface;
};

