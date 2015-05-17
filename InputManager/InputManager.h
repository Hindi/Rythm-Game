#pragma once

#include <SFML/Window.hpp>
#include "..\Interface\UInterface.h"
#include "..\entity\Player.h"
#include "..\utility\EventManager.hpp"
#include "..\utility\GameState\GameStateManager.h"

	/**
	 * @class	InputManager
	 *
	 * @brief	Manager for SFML events. Calls the GameStateManager on input.
	 *
	 * @author	Quentin
	 * @date	09/06/2014
	 */

class InputManager
{
public:
	InputManager(Player &player, GameStateManager &gameStateManager);
	void checkInput( sf::RenderWindow & window);
	~InputManager();

private :
	Player& m_player;
	GameStateManager& m_gameStateManager;
};