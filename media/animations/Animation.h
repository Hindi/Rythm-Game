#ifndef ANIMATION
#define ANIMATION

#include "Anim.h"
#include <iostream>
#include <memory>
#include <assert.h>

	/**
	 * @brief	Sprite anim� qui utilise un objet de type anim (vector de frame), fait d�filer les frames avec un temps m_time entre chaque frame 
	 * 			et dispose de nombreuses m�thodes pour modifier les propri�t�s de l'a nimation. 
	 * 			z-index d�finit la hauteur d'affichage d'un �l�ment 
	 *
	 *
	 * @author	Vincent
	 * @date	01/06/2014
	 *
	 */

/* EXAMPLE DE CREATION ET D'UTILISATION D'UNE ANIMATION :

	//Cr�er les anims et images n�cessaires
	Anim m_anim, goRight;
	sf::Image image;

	//Charger les images
	image.loadFromFile(std::string Path);
	
	//Remplir les anim avec des morceaux d'images
	m_anim.pushFrame(Frame(image, sf::Rect<int>(0, m_frameHeight, m_frameWidth, m_frameHeight)));
	goRight.pushFrame(Frame(image, sf::Rect<int>(m_frameWidth,0,m_frameWidth,m_frameHeight)));
	goRight.pushFrame(Frame(image, sf::Rect<int>(m_frameWidth*3,0,m_frameWidth,m_frameHeight)));
	
	//Cr�er l'objet Animation (voir diff�rents constructeurs)
	Animation* m_animated = new Animation();

	//Ajouter les anim � jouer
	m_animated->addAnim("main", &m_anim);
	m_animated->addAnim("goRight", &goRight);

	//S�lectionner l'anim � jouer
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

        // Par d�fault
		Animation(int zIndex=100, bool Play = false, bool Loop = true, float Time = 0.f);

        // Directement avec une Anim
		Animation(std::shared_ptr<Anim> NewAnim, int zIndex = 100, bool Play = false, bool Loop = true, float Time = 0.f);

        // Destructeur
        virtual ~Animation();

        // Utilisation d'une naimation courante (non sauvegard�e)
		void setAnim(std::shared_ptr<Anim> NewAnim);

        // Retourne un pointeur sur l'anim
		std::shared_ptr<Anim> getAnim();

        // Passer � l'image num�ro X
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

        // Est stopp� ?
        bool isStoped();

        //Permet de faire avancer l'animation en fonction du temps �coul� depuis le dernier appel
		void anim(float ElapsedTime);

		//Ajoute une animation sous le nom "name"
		void addAnim(std::string const &name, std::shared_ptr<Anim> newAnim);

		// D�finit l'animation s�lectionn�e comme animation active
		void setAnim(std::string const &animName, bool play);

		//D�finit si l'animation sera affich�e � l�cran
		void setDrawable(bool draw);
		bool isDrawable();
		bool operator==(const Animation& anim);

		int size() const;
		int zIndex() const;

    private:

		// Passer � l'image num�ro X
		void doSetFrame(int Frame);
		//Permet de faire avancer l'animation en fonction du temps �coul� depuis le dernier appel
		void doAnim(float ElapsedTime);

        float m_time;					//Le temps que l'on souhaite entre chaque frame
        float m_elapsedTime;			//Variable dans laquelle on retranche le temps jusqu'aau changement de frame
        bool Paused;					//Animatio nen pause ou non
        bool m_loop;					//Animation en boucle ou non
		bool m_drawable;				//Doit �tre dessin� ou non
		std::shared_ptr<Anim> m_anim;					//Le vector de frame courrement utilis�
        int m_currentFrame;				//Frame active		
		int m_zIndex;					//D�finit la hauteur d'affichage
        std::map< std::string, std::shared_ptr<Anim> > m_animations;	//Liste d'images avec leur nom

		//V�rifie si l'animation demand� n'est pas d�j� dans la map
		bool isStored(std::string const &name) const ;
};

#endif
