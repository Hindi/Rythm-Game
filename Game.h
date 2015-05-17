#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "media\animations\Anim.h"
#include "media\animations\Frame.h"
#include "media\animations\Animation.h"
#include "media\animations\AnimationManager.h"
#include "media\MediaManager.hpp"
#include "media\sons\SoundManager.h"
#include "InputManager\InputManager.h"
#include "entity\Player.h"
#include "Interface\UInterface.h"
#include "utility\GameState\GameStateManager.h"
#include "utility\EventManager.hpp"
#include "level\LevelBuilder.h"
#include "Physic\Physic.h"
#include "level\Background.h"


/**
* @brief	The whole game starts here.
*
* @author	Vincent
* @date	09/06/2014
*
*/

class Game
{
public:
	Game();
	~Game();
	void start();

	//Events
	void triggerFreeze(bool pause);

private:
	bool paused;
};

