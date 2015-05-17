#pragma once

#include <assert.h>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

#include "../MediaManager.hpp"
#include "../../utility/EventManager.hpp"
#include "../../level/LevelManager.h"

/**
	* @class	SoundManager
	*
	* @brief	Class used to play sounds. It keeps sf::Sounds in a map (sf::Sounds are built from
	* 			sf::SoundBuffer which are kept in the MediaManager).
	*
	* @author	Vincent
	* @date	09/06/2014
	*/

class SoundManager
{
public:
	SoundManager(LevelManager &levelManager);
	~SoundManager();
	void playSound(std::string name, float volume = 50);
	int getMediaLoadedAmout();
	void triggerNextSound(std::string soundName);

private:
	//Si le son demandé est déjà en mémoire, le joue. Sinon, créé un nouveau son en faisant appel au MediaManagerp our le charger
	void doPlaySound(std::string name, float volume);
	
	//Conserve les sons en mémoire
	std::map<std::string, sf::Sound> m_sounds;

	LevelManager &m_levelManager;
};

