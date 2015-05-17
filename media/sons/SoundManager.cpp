#include "SoundManager.h"

/**
 * @fn	SoundManager::SoundManager(LevelManager &levelManager)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	levelManager	Manager for level.
 */
SoundManager::SoundManager(LevelManager &levelManager) :
m_levelManager(levelManager)
{
	EventManager<std::string>::getInstance().addListener("sucessfullJump", std::bind(&SoundManager::triggerNextSound, this, std::placeholders::_1));
}

/**
 * @fn	SoundManager::~SoundManager()
 *
 * @brief	Destructor.
 *
 */
SoundManager::~SoundManager()
{

}

/**
 * @fn	void SoundManager::playSound(std::string name)
 *
 * @brief	Assers before doPlaySound
 *
 * @author	Vincent
 * @date	09/06/2014
 *
 * @param	name	The name.
 */
void SoundManager::playSound(std::string name, float volume)
{
	assert(name != "");
	doPlaySound(name, volume);
}

/**
 * @fn	void SoundManager::doPlaySound(std::string name)
 *
 * @brief	Plays the sounds if it's already in the map, if not, use the MediaManager to load them before.
 *
 * @author	Vincent
 * @date	09/06/2014
 *
 * @param	name	The name.
 */
void SoundManager::doPlaySound(std::string name, float volume)
{
	//Si le son n'est pas déjà créé
	if (!m_sounds.count(name))
	{
		//On créé un nouveau son et on demande au MediaManager de charger le SoundBuffer qu'il faut
		sf::Sound sound;
		sound.setBuffer(MediaManager<sf::SoundBuffer>::getInstance().getMedia("../JIN4/media/sons/" + name));
		m_sounds[name] = sound;
	}
	//On joue finalement le son
	m_sounds[name].setVolume(volume);
	m_sounds[name].play();
}

/**
* @fn	int SoundManager::getMediaLoadedAmout()
*
* @brief	Return the number of souns in memory, for unit tests.
*
* @return	The media loaded amout.
*/

int SoundManager::getMediaLoadedAmout()
{
	return m_sounds.size();
}

/**
 * @fn	void triggerNextSound()
 *
 * @brief	Play next sound.
 *
 */
void SoundManager::triggerNextSound(std::string soundName)
{
	playSound(soundName);
}