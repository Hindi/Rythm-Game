#include "Game.h"

/**
 * @fn	Game::Game()
 *
 * @brief	Default constructor.
 *
 */
Game::Game() :
paused(false)
{
	EventManager<bool>::getInstance().addListener("freeze", std::bind(&Game::triggerFreeze, this, std::placeholders::_1));
}

/**
 * @fn	Game::~Game()
 *
 * @brief	Destructor.
 *
 */
Game::~Game()
{
}

/**
 * @fn	void Game::triggerFreeze(bool pause)
 *
 * @brief	Trigger freeze.
 *
 *
 * @param	pause	true to pause.
 */
void Game::triggerFreeze(bool pause)
{
	paused = pause;
}

/**
 * @fn	void Game::start()
 *
 * @brief	main function.
 *
 */
void Game::start()
{
	//Instantiate the player
	Player player(200, 410);

	//LevelManager, parse the levels from files in ./level
	LevelManager levelManager;

	//LevelBuilder builds the levels
	LevelBuilder levelBuilder(levelManager);

	//User interface
	UInterface interface(levelManager);

	//A simple state machine
	GameStateManager gameStateManager(player, interface);

	//InputManager that communicate the inputs to the state machine
	InputManager inputManager(player, gameStateManager);

	//SoundManager play sounds on demand
	SoundManager soundManager(levelManager);

	//Manages the collisions and movements
	Physic Physic(levelBuilder, player);

	//Background, for a funkier game
	Background m_background;

	//The SFML window
	sf::RenderWindow window(sf::VideoMode(800, 600), "");

	//Uncomment to test the melodies without losing
	//EventManager<void>::getInstance().call("debug");

	while (window.isOpen())
	{
		//Clear the screen
		window.clear(sf::Color::White); 

		//Check the input
		inputManager.checkInput(window);

		//Move everything and check the collisions
		Physic.computePhysic();

		//Update and draw the background
		m_background.updateBackground(window);

		//Update and draw all the animations
		AnimationManager::getInstance().updateAnimation(window, paused);

		//Draw the UI
		interface.update(window);

		//Instantiate the obstacles
		levelBuilder.update();

		//Display everything on screen
		window.display();  

		sf::sleep(sf::milliseconds(1));
	}
}