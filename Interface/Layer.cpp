#include "Layer.h"


Layer::Layer()
{
}


Layer::~Layer()
{
}

/**
 * @fn	void Layer::draw(sf::RenderWindow &window)
 *
 * @brief	Draws the sf::text.
 *
 * @param [in,out]	window	The window.
 */
void Layer::draw(sf::RenderWindow &window)
{
	if (drawable)
		window.draw(m_text);
}