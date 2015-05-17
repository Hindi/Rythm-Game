#pragma once
#include <memory>

#include "GameState.h"
#include "GameStatePause.h"
#include "GameStateManager.h"
#include "GameStateEndGame.h"

	/**
	 * @class	GameStateGame
	 *
	 * @brief	When the player is actually playing
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 */

class GameStateGame : public GameState
{
public:
	GameStateGame(GameStateManager& gameStateManager, Player &player);
	virtual ~GameStateGame();

	virtual void start();
	virtual void end();
	void inputKeyReturn();
	void inputKeyEscape();
	void inputKeyUp();
	void inputKeyDown();
	void triggerDeath();


	Player &m_player;
};

