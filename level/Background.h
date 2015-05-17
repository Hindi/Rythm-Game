#pragma once 
#include "..\utility\EventManager.hpp"
#include<SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <list>
/**
* @class	Background
*
* @brief	Class which is in charge of compute and draw the background graphics
*
* @author	Quentin
* @date	17/06/2014
*/

class Background
{
public: 
	Background();
	~Background();
	void updateBackground(sf::RenderWindow & window);
	void addCircle();
private : 
	sf::CircleShape m_circle;
	sf::Color m_color;


};