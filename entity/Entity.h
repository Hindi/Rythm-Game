#pragma once

#include <SFML/Graphics.hpp>
#include "..\media\animations\Animation.h"

	/**
	 * @class	Entity
	 *
	 * @brief	 Parent class for all the objects who will be print on screen
	 *
	 * @author	Quentin
	 * @date	09/06/2014
	 */

class Entity
{
public:
	#pragma region constructeurs 
	Entity();
	Entity(float x, float y);
	Entity(sf::Vector2f pos, float w, float h);
	Entity(sf::Vector2f pos, float w, float h, sf::Vector2f speed, int weight, std::shared_ptr<Animation> anim);
	#pragma endregion

	#pragma region méthodes

	void moveTo(sf::Vector2f const &nPos);
	void translate(sf::Vector2f const &tVector);
	virtual void setAnim(std::string const &animName, bool startWhenReady);
	virtual void incSpeed(sf::Vector2f s);
	

	#pragma region get()
	sf::Vector2f getPosition();
	float getHeight();
	float getWidth();
	sf::Vector2f getSpeed();
	int getWeight();
	sf::Rect<float> getBox();
	#pragma endregion

	#pragma region set()
	void setBox(float x, float y, float w, float h);
	void setBoxWithoutAnim(float x, float y, float w, float h);
	void setHeight(float h);
	void setWidth(float w);
	void setSpeed(sf::Vector2f s);
	void setWeight(int w);
	void setAnimation(std::shared_ptr<Animation> anim);
	#pragma endregion	

	#pragma endregion

	~Entity();

protected:

	virtual void createAnimation() = 0;


	sf::Rect<float> m_box;
	sf::Vector2f m_speed;
	int m_weight;
	std::shared_ptr<Animation> m_animation;
};

