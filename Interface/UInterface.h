#pragma once

#include <memory>
#include <string>

#include "..\utility\EventManager.hpp"
#include "..\media\animations\Frame.h"
#include "..\media\animations\Anim.h"
#include "..\media\animations\Animation.h"
#include "..\media\animations\AnimationManager.h"
#include "..\media\MediaManager.hpp"
#include "Layer.h"
#include "../level/LevelManager.h"

	/**
	 * @class	UInterface
	 *
	 * @brief	The user interface.
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 */

class UInterface
{
public:
	UInterface(LevelManager& levelManager);
	~UInterface();

	void update(sf::RenderWindow& window);

	//Events
	void triggerPause(bool pause);
	void triggerLost(bool lose);
	void triggerPlay();
	void triggerIntro(bool intro);
	void triggerScore();
	void incrementLevelSelect();
	void decrementLevelSelect();
	void startLevel();

private:
	Layer createLayer(std::string text, sf::Color color, int size, sf::Vector2f position);
	void updateLevelListPosition();

	int m_levelSelect;
	int m_scoreCount;
	std::vector<Layer> m_levelList;
	sf::Font m_font;
	sf::Font m_font2;
	Layer m_pauseMenu;
	Layer m_loseMenu;
	Layer m_input;
	Layer m_Score;
	std::shared_ptr<Animation> animationSelecteur;
	LevelManager &m_levelManager;
};