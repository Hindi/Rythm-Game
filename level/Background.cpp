#include "Background.h"

/**
* @fn	Background::Background()
*
* @brief	constructor
*
*
*@return	The sound name.
*/

Background::Background():
m_circle(30, 60), m_color(0, 0, 0, 0)
{
	m_circle.setPosition(240, 460);
	m_circle.setOutlineThickness(650);
	EventManager<std::string>::getInstance().addListener("sucessfullJump", std::bind(&Background::addCircle, this));

}

Background::~Background()
{

}

/**
* @fn	Background::updateBackground(sf::RenderWindowd & window)
*
* @brief	update the Background's graphic
*
*
* @param	window a reference to the renderwindow
*/

void Background::updateBackground(sf::RenderWindow & window)
{
	m_circle.setOutlineColor(m_color);
	window.draw(m_circle);
	m_circle.setRadius(m_circle.getRadius() + 2.5);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());

}


/**
* @fn	Background::addCircle(sf::RenderWindowd & window)
*
* @brief	reset the background cricle and change the color, call by an event
*
*
*/

void Background::addCircle()
{	
	m_color.r = rand() % 255 ;
	m_color.g = rand() % 255 ;
	m_color.b = rand() % 255 ;
	m_color.a =75;
	m_circle.setRadius(20);
	m_circle.setOrigin(20, 20);

}