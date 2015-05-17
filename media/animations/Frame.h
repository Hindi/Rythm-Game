#ifndef FRAME
#define FRAME

#include <SFML/Graphics.hpp>

 /**
  * @class	Frame
  *
  * @brief	Une Frame est composée d'un pointeur sur une texture, d'un SubRect et d'une couleur
  *			La couleur par défaut d'une Frame est le blanc.
  *			La texture contenue dans une frame est la partie de la texture pointée contenue dans le subRect.
  *
  * @author	Vincent
  * @date	09/06/2014
  */

/*
 
 */

class Frame
{
    public:
		// Par défaut
		Frame(const sf::Color& NewColor = sf::Color::White);

		// Par copie
		Frame(const Frame& Cpy);

		// texture et Rect
		Frame(sf::Image& NewImage, const sf::Rect<int>& NewRect, const sf::Color& NewColor = sf::Color::White);

		// texture (Le Rect est a la dimension de la texture)
		Frame(sf::Texture Newtexture, const sf::Color& NewColor = sf::Color::White);

		// destructeur
		virtual ~Frame();

		//Get the sf::Texture
		sf::Texture& getTexture();

private:
		// Accès public à la texture, au Rect et à la couleur
		sf::Texture texture;

		sf::Rect<int> Rect;

		sf::Color Color;
};

#endif // FRAME
