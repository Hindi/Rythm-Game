#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <assert.h>

	/**
	 * @brief	Generic Singleton class use to load sounds and images with sfml.
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 *
	 */


template<class T> class MediaManager
{
public:

	/**
	 * @fn	const T& MediaManager::getMedia(const std::string& filename)
	 *
	 * @brief	Asserts before doGetMedia.
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	The media.
	 */
	const T& getMedia(const std::string& filename)
	{
		assert(filename != "");
		return doGetMedia(filename);
	}

	/**
	 * @fn	bool MediaManager::push(const std::string& filename)
	 *
	 * @brief	Asserts before doPush.
	 *
	 * @param	filename	The filename to push.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	bool push(const std::string& filename)
	{
		assert(filename != "");
		return doPush(filename);
	}

	/**
	 * @fn	static MediaManager<T>& MediaManager::getInstance()
	 *
	 * @brief	Gets the instance of the singleton.
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 *
	 * @return	The instance.
	 */
	static MediaManager<T>& getInstance()
	{
		static MediaManager<T> manager;
		return manager;
	}

	/**
	* @fn	int MediaManager::getMediaLoadedAmout()
	*
	* @brief	Return the number of medias in memory, for unit tests.
	*
	* @return	The media loaded amout.
	*/

	int getMediaLoadedAmout()
	{
		return m_medias.size();
	}

private:

	/**
	 * @fn	bool MediaManager::doPush(const std::string& filename)
	 *
	 * @brief	Try to add a media to the map and return a true if it succeeded.
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	bool doPush(const std::string& filename)
	{
		T buffer;
		//On cherche dans le dossier principal du projet
		if (buffer.loadFromFile(filename))
		{
			m_medias[filename] = buffer;
			return true;
		}
		return false;
	}

	/**
	 * @fn	const T& MediaManager::doGetMedia(const std::string& filename)
	 *
	 * @brief	Check if the media is in the map already. If it's not, use the push function to load it, then returns it.
	 *
	 * @param	filename	Filename of the file.
	 *
	 * @return	A T&amp;
	 */
	const T& doGetMedia(const std::string& filename)
	{
		//On vérifie que le media n'est pas déjà chargé
		if (m_medias.count(filename))
		{
			return m_medias[filename];
		}

		//Le media n'existe pas, on le créé et on le sauvegarde
		T buffer;
		buffer.loadFromFile(filename);
		m_medias[filename] = buffer;
		if (push(filename))
			return m_medias[filename];

		std::cout << "ERROR: MediaManager | Impossible de trouver le media : " << filename << std::endl;
		m_medias[filename] = buffer;
		return m_medias[filename];
	}

	MediaManager(){}
	std::map<std::string, T> m_medias;			//Map des medias avec le nom

};