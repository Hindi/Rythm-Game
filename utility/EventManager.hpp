#pragma once
#include <map>
#include <string>
#include <utility>
#include <map>
#include <functional>
#include "Delegate.hpp"

	/**
	 * @Summary		Pour mettre en place un évènement, il faut enregistrer dans l'EventManager les fonctions à appeler quand un event trigger.
	 *				Pour ça il faut appeller addListener() en précisant le nom de l'event et la fonction à appeler. Cette fonction doit sortir d'un std::bind (lire la doc std::bind et std::placeholders).
	 *				Exemple pour ajouter un listener sur l'event "up" dans l'objet Game : EventManager<int>::getInstance().addListener("up", std::bind(&Game::value, &(*this), std::placeholders::_1));
	 *
	 *				Un template variadique est utilisé pour permettre d'utiliser des fonctions avec un nombre de paramètres variable.
	 *				Pour trigger un event, on utilise simplement la fonction call() avec le nom de l'event et les arguments nécessaires.
	 *				Dans le cas de l'exemple précédent, on écrirait : EventManager<int>::getInstance().call("up", 5);
	 *
	 *				Autre exemple (pour afficher les stats en fin de niveau, par exemple) :
	 *				EventManager<int, int, int>::getInstance().addListener("endGame", std::bind(&Menu::printStat, &(*this), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	 *				EventManager<int, int, int>::getInstance().call(50, 30, 215);
	 */

/*
	

*/

template<typename... Arguments> class EventManager
{
public:
	/**
	 * @fn	void EventManager::addListener(std::string name, std::function<void(Arguments...)> func)
	 *
	 * @brief	Adds a listener to the event named "name" and link it with the function "func" that'll be called when the event trigers.
	 *
	 * @param	name	The name of the event that'll call this function on trigger.
	 * @param	func	A pointer to the function to store
	 */
	void addListener(std::string name, std::function<void(Arguments...)> func)
	{
		funcs[name].add(func);
	}

	/**
	 * @fn	void EventManager::call(std::string evtName, Arguments... t)
	 *
	 * @brief	Calls the functions registered for the event evtName.
	 *
	 * @param	evtName	Name of the event.
	 * @param	t		List of the arguments necessary to call these functions.
	 */
	void call(std::string evtName, Arguments... t)
	{
		if (funcs.find(evtName) != funcs.end())
			funcs[evtName].call(t ...);
	}

	/**
	 * @fn	static EventManager<Arguments...>& EventManager::getInstance()
	 *
	 * @brief	Gets the instance of the singleton.
	 *
	 * @return	The instance.
	 */
	static EventManager<Arguments...>& getInstance()
	{
		static EventManager<Arguments...> manager;
		return manager;
	}

private:

	EventManager(){}
	std::map< std::string, Delegate<Arguments...> > funcs;
};

/**
 * @class	EventManager<void>
 *
 * @brief	Specialisation for 0 parameters
 *
 */
template<> class EventManager<void>
{
public:
	/**
	* @fn	void EventManager::addListener(std::string name, std::function<void(Arguments...)> func)
	*
	* @brief	Adds a listener to the event named "name" and link it with the function "func" that'll be called when the event trigers.
	*
	* @param	name	The name of the event.
	* @param	func	The function.
	*/
	void addListener(std::string name, std::function<void()> func)
	{
		funcs[name].add(func);
	}

	/**
	* @fn	void EventManager::call(std::string evtName, Arguments... t)
	*
	* @brief	Calls the functions registered for the event evtName.
	*
	* @param	evtName	Name of the event.
	*/
	void call(std::string evtName)
	{
		if (funcs.find(evtName) != funcs.end())
			funcs[evtName].call();
	}

	/**
	* @fn	static EventManager<Arguments...>& EventManager::getInstance()
	*
	* @brief	Gets the instance of the singleton.
	*
	* @return	The instance.
	*/
	static EventManager<void>& getInstance()
	{
		static EventManager manager;
		return manager;
	}

private:

	EventManager(){}
	std::map< std::string, Delegate<>  > funcs;
};