#pragma once

#include "GameState.h"
#include "GameStateGame.h"
#include "GameStateManager.h"
#include "../../Interface/UInterface.h"
#include <memory>

	/**
	 * @class	GameStateIntro
	 *
	 * @brief	The state when the game starts.
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 */

class GameStateIntro : public GameState
{
public:
	GameStateIntro(GameStateManager& gameStateManager, UInterface &interface);
	virtual ~GameStateIntro();

	virtual void start();
	virtual void end();
	void inputKeyReturn(); 
	void inputKeyEscape();
	void inputKeyUp();
	void inputKeyDown();
	void triggerPlay();

	UInterface &m_interface;
};

