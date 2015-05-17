#include "InputManager.h"

InputManager::InputManager(Player &player, GameStateManager &gameStateManager) :
	m_player(player),
	m_gameStateManager(gameStateManager)
{
}

/**
 * @fn	void InputManager::checkInput(sf::RenderWindow & window)
 *
 * @brief	Check inputs and sends them to the GameStateManager.
 *
 * @param [in,out]	window	The window.
 */
void InputManager::checkInput(sf::RenderWindow & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Fermeture de la fenêtre
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			#pragma region switch (event.key.code)
			switch (event.key.code)
			{

			case sf::Keyboard::Up:
			{
				m_gameStateManager.inputKeyUp();
				break;
			}

			case sf::Keyboard::Down:
			{
				m_gameStateManager.inputKeyDown();
				break;
			}

			case sf::Keyboard::Left:
			{
				/* on appelle les fonctions correspondantes
				m_player -> do();
				m_interface -> do();
				*/
				break;
			}

			case sf::Keyboard::Right:
			{
				/* on appelle les fonctions correspondantes
				m_player -> do();
				m_interface -> do();
				*/
				break;
			}

			case sf::Keyboard::Escape:
			{
				m_gameStateManager.inputKeyEscape();
				break;
			}

			case sf::Keyboard::Return:
			{
				m_gameStateManager.inputKeyReturn();
				break;
			}
			default:
				break;
			}
#pragma endregion
		}

	}
	
}

InputManager::~InputManager()
{

}