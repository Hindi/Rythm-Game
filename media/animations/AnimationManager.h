#ifndef ANIMATION_MANAGER
#define ANIMATION_MANAGER


#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Anim.h"
#include "../MediaManager.hpp"
#include "../../utility/EventManager.hpp"
#include "Frame.h"

	/**
	 * @brief	Classe qui contient des pointeurs vers toutes les animations. Elle permet de créer les animations, les anims associés, 
	 * 			et d'actualiser toutes les animations du jeu en même temps avec une seule et unique sf::Clock.
	 *
	 * @author	Vincent
	 * @date	16/06/2014
	 */

/*	EXAMPLE DE CREATION ET D'UTILISATION D'UNE ANIMATION :

	Animation* m_animated = animationManager->addAnimation();
	animationManager->addAnim(m_animated, "chemin vers l'image" ,rects, "nom de l'animation");
    
	//Les options voulues (play, position, stop, etc)

	m_animated->setAnim("goRight", true);

    while (window.isOpen())
    {
		animationManager->updateAnimation(window);
    }

*/

class AnimationManager
{
    public:
		static AnimationManager& getInstance();
		// Destructeur
		~AnimationManager();
		
		//Ajoute une animation au vector d'animation
		std::shared_ptr<Animation> addAnimation(std::shared_ptr<Animation> Cpy);
		
        //Ajoute une animation au vector d'animation
		std::shared_ptr<Animation> addAnimation(bool Play = false, bool Loop = true, float Time = 0.f);

		//Créé un objet Anim et l'attribut à une animation
		void addAnim(std::shared_ptr<Animation> animation, std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name);
		void addAnim(std::shared_ptr<Animation> animation, const char filename[], std::vector< sf::Rect<int> > rects, const char name[]);

		//Créé et retourne un pointeur sur Anim
		std::shared_ptr<Anim> createAnim(std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name);

		//Met à jour les animations et les dessine
		void updateAnimation(sf::RenderWindow& window, bool paused);

		void reset();

    private:

		sf::Clock clock;						//Horloge pour actualiser les animations
		std::vector<std::shared_ptr<Animation> > m_animations;	//L'ensemble des animations en jeu et leurs noms

        AnimationManager();

};


#endif