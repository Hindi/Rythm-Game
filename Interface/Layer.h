#pragma once

#include <SFML\Graphics.hpp>

/**
 * @class	Layer
 *
 * @brief	A layer used in the interface.
 *
 * @author	Vincent
 * @date	17/06/2014
 */

class UInterface;
class Layer
{

	friend UInterface;

public:
	Layer();
	~Layer();
	void draw(sf::RenderWindow &window);

private:
	sf::Text m_text;
	bool drawable;
};

