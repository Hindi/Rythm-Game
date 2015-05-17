#pragma once
#include <memory>

#include "GameState.h"
#include "GameStateManager.h"
#include "../../Interface/UInterface.h"

/**
 * @class	GameStateEndGame
 *
 * @brief	A game state called when the player lose.
 *
 * @author	Vincent
 * @date	16/06/2014
 */

class GameStateGame;
class GameStateEndGame : public GameState
{
public:
	GameStateEndGame(GameStateManager& gameStateManager, UInterface &interface);
	~GameStateEndGame();

	virtual void start();
	virtual void end();
	void inputKeyReturn();
	void inputKeyEscape();
	void inputKeyUp();
	void inputKeyDown();
	UInterface &m_interface;
};

