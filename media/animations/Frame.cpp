#include "Frame.h"

/**
 * @fn	Frame::Frame(const sf::Color& NewColor)
 *
 * @brief	Constructor.
 *
 * @param	NewColor	The new color.
 */
Frame::Frame(const sf::Color& NewColor)
{
    Color = NewColor;
}

/**
 * @fn	Frame::Frame(const Frame& Cpy)
 *
 * @brief	Copy constructor.
 *
 * @param	Cpy	The copy.
 */
Frame::Frame(const Frame& Cpy)
{
    texture = Cpy.texture;
    Rect = Cpy.Rect;
    Color = Cpy.Color;
}

/**
 * @fn	Frame::Frame(sf::Image& NewImage, const sf::Rect<int>& NewRect, const sf::Color& NewColor)
 *
 * @brief	Constructor.
 *
 * @param [in,out]	NewImage	The new image.
 * @param	NewRect				The new rectangle.
 * @param	NewColor			The new color.
 */
Frame::Frame(sf::Image& NewImage, const sf::Rect<int>& NewRect, const sf::Color& NewColor)
{
	texture.loadFromImage(NewImage, NewRect);
    Rect = NewRect;
    Color = NewColor;
}

/**
 * @fn	Frame::Frame(sf::Texture Newtexture, const sf::Color& NewColor)
 *
 * @brief	Constructor.
 *
 * @param	Newtexture	The newtexture.
 * @param	NewColor  	The new color.
 */
Frame::Frame(sf::Texture Newtexture, const sf::Color& NewColor)
{
    texture = Newtexture;
    Rect = sf::Rect<int>(0, 0, texture.getSize().x, texture.getSize().y);

    Color = NewColor;
}

/**
 * @fn	Frame::~Frame()
 *
 * @brief	Destructor.
 *
 */

Frame::~Frame()
{

}

/**
 * @fn	sf::Texture Frame::getTexture()
 *
 * @brief	Gets the texture.
 *
 * @return	The texture.
 */
sf::Texture& Frame::getTexture()
{
	return texture;
}