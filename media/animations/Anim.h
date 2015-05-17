#ifndef ANIM
#define ANIM

#include <vector>
#include <iostream>
#include <string>

#include "Frame.h"

	/**
	 * @class	Anim
	 *
	 * @brief	 La classe animation n'est qu'un vector de Frame
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 */

class Anim
{
    public:

		// par d�faut
		Anim(); 

		//Avec un nom
		Anim(std::string name);

		// destructeur
		virtual ~Anim();

		// Par copie
		Anim(const Anim& Cpy);

		// Ajouter une Frame
		void pushFrame(const Frame& NewFrame);

		// Nombre de Frame(s)
		size_t size() const;

		// Acc�s a la frame num�ro N
		Frame& operator [] (size_t N);
		
		// Acc�s a la frame num�ro N
		Frame& getFrame(size_t N);

		bool isLastFrame(int frameNumber);

		//Lib�rer les frame
		void reset();

		//Donner un nom � l'anim
		void setName(std::string name);

		//Retourner le nom de l'anim
		std::string getName() const;

		bool operator==(const Anim& anim);

    private:
		std::string m_name;				//Nom de l'anim
		std::vector< Frame > m_frame;	//Vector des frames

};
#endif
