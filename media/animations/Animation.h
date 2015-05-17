#ifndef ANIMATION
#define ANIMATION

#include "Anim.h"
#include <iostream>
#include <memory>
#include <assert.h>

	/**
	 * @brief	Sprite animé qui utilise un objet de type anim (vector de frame), fait défiler les frames avec un temps m_time entre chaque frame 
	 * 			et dispose de nombreuses méthodes pour modifier les propriétés de l'a nimation. 
	 * 			z-index définit la hauteur d'affichage d'un élément 
	 *
	 *
	 * @author	Vincent
	 * @date	01/06/2014
	 *
	 */

/* EXAMPLE DE CREATION ET D'UTILISATION D'UNE ANIMATION :

	//Créer les anims et images nécessaires
	Anim m_anim, goRight;
	sf::Image image;

	//Charger les images
	image.loadFromFile(std::string Path);
	
	//Remplir les anim avec des morceaux d'images
	m_anim.pushFrame(Frame(image, sf::Rect<int>(0, m_frameHeight, m_frameWidth, m_frameHeight)));
	goRight.pushFrame(Frame(image, sf::Rect<int>(m_frameWidth,0,m_frameWidth,m_frameHeight)));
	goRight.pushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3,0,m_frameWidth,m_frameHeight)));
	
	//Créer l'objet Animation (voir différents constructeurs)
	Animation* m_animated = new Animation();

	//Ajouter les anim à jouer
	m_animated->addAnim("main", &m_anim);
	m_animated->addAnim("goRight", &goRight);

	//Sélectionner l'anim à jouer
	m_animated->setAnim("main", true);

    while (window.isOpen())
    {
        m_animated->anim(elapsed.asSeconds()*10);
		window.draw(*m_animated);
    }

*/

class Animation : public sf::Sprite
{
    public:
        // Par Copie
        Animation(const Animation& Cpy);

        // Par défault
		Animation(int zIndex=100, bool Play = false, bool Loop = true, float Time = 0.f);

        // Directement avec une Anim
		Animation(std::shared_ptr<Anim> NewAnim, int zIndex = 100, bool Play = false, bool Loop = true, float Time = 0.f);

        // Destructeur
        virtual ~Animation();

        // Utilisation d'une naimation courante (non sauvegardée)
		void setAnim(std::shared_ptr<Anim> NewAnim);

        // Retourne un pointeur sur l'anim
		std::shared_ptr<Anim> getAnim();

        // Passer à l'image numéro X
        void setFrame(int Frame);

        // Retourne la Frame courante
        int getCurrentFrame();

        // Fixer le temps entre chaques Frame
        void setFrameTime(float Time);

        // Retourne le temps entre chaques Frame
        float getFrameTime();

        // Jouer en boucle ?
        void setLoop(bool Loop);

        // Jouer en boucle ?
		bool isLoop();

		// Jouer en boucle ?
		bool hasended();

        // Met en pause la lecture
        void pause();

        // Relance la lecture
        void play();

        // Met en pause la lecture et rembobine
        void stop();

        // Est en pause ?
        bool isPaused();

        // Est stoppé ?
        bool isStoped();

        //Permet de faire avancer l'animation en fonction du temps écoulé depuis le dernier appel
		void anim(float ElapsedTime);

		//Ajoute une animation sous le nom "name"
		void addAnim(std::string const &name, std::shared_ptr<Anim> newAnim);

		// Définit l'animation sélectionnée comme animation active
		void setAnim(std::string const &animName, bool play);

		//Définit si l'animation sera affichée à lécran
		void setDrawable(bool draw);
		bool isDrawable();
		bool operator==(const Animation& anim);

		int size() const;
		int zIndex() const;

    private:

		// Passer à l'image numéro X
		void doSetFrame(int Frame);
		//Permet de faire avancer l'animation en fonction du temps écoulé depuis le dernier appel
		void doAnim(float ElapsedTime);

        float m_time;					//Le temps que l'on souhaite entre chaque frame
        float m_elapsedTime;			//Variable dans laquelle on retranche le temps jusqu'aau changement de frame
        bool Paused;					//Animatio nen pause ou non
        bool m_loop;					//Animation en boucle ou non
		bool m_drawable;				//Doit être dessiné ou non
		std::shared_ptr<Anim> m_anim;					//Le vector de frame courrement utilisé
        int m_currentFrame;				//Frame active		
		int m_zIndex;					//Définit la hauteur d'affichage
        std::map< std::string, std::shared_ptr<Anim> > m_animations;	//Liste d'images avec leur nom

		//Vérifie si l'animation demandé n'est pas déjà dans la map
		bool isStored(std::string const &name) const ;
};

#endif
