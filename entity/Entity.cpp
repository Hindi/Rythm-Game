#include "Entity.h"


#pragma region constructeurs 

/**
* @fn	Entity::Entity()
*
* @brief	Constructor 
*/

Entity::Entity()
{

}

/**
* @fn	Entity::Entity(float x, float y)
*
* @brief	Constructor with x and y postion.
*
* @param	x					The x Position.
* @param	y					The y Position.
*/

Entity::Entity(float x, float y) :
m_box(x, y, 0, 0)
{
	m_speed = sf::Vector2f(0, 0);
	m_weight = 0;
	m_animation = NULL;
}

/**
* @fn	Entity::Entity(sf::vector2i pos,int w, int h)
*
* @brief	Constructor with x/y position, width and height of the object.
*
* @param	pos					The vector2i position.
* @param	w					The width.
* @param	h					The height.
*/

Entity::Entity(sf::Vector2f pos,float w, float h):
m_box(pos.x, pos.y, w, h)
{
	m_speed = sf::Vector2f(0, 0);
	m_weight = 0;
	m_animation = NULL;
}

/**
* @fn	Entity::Entity(sf::vector2i pos, int w, int h, int speed, int weight, Animation * anim)
*
* @brief	The complete Constructor of Entity

* @param	pos					The vector2i position.
* @param	w					The width.
* @param	h					The height.
* @param	speed				The speed.
* @param	weight				The weight.
* @param	anim				A pointer to the animation we want.
*/

Entity::Entity(sf::Vector2f pos, float w, float h, sf::Vector2f speed, int weight, std::shared_ptr<Animation> anim) :
m_box(pos.x, pos.y, w, h)
{	
	m_speed = speed;
	assert(weight >= 0);
	m_weight = weight;
	assert(anim != NULL);
	m_animation = anim;
	m_animation->setPosition(pos);
}

#pragma endregion

#pragma region méthodes

/**
* @fn	void Entity::moveTo(sf::vector2i const &nPos)
*
* @brief	move the Entity to the donate coordinate
*
* @param	nPos				The vector2i new position.
*/

void Entity::moveTo(const sf::Vector2f &nPos)
{
	m_box.left = nPos.x;
	m_box.top = nPos.y;
	m_animation->setPosition(nPos);
}

/**
* @fn	void Entity::moveTo(sf::vector2i const &nPos)
*
* @brief	move the Entity by the vector
*
* @param	tVector				The translation Vector.
*/


void Entity::translate(const sf::Vector2f &tVector)
{	

	m_box.left += tVector.x;
	m_box.top += tVector.y;
	m_animation->setPosition( m_animation->getPosition() + tVector);
}

/**
* @fn	void Entity::setAnim(std::string const &animName, bool startWhenReady)
*
* @brief	set the anim to be display of the entity
*
* @param	animName			The name of the anim
*/


void Entity::setAnim(std::string const &animName, bool startWhenReady)
{
	m_animation->setAnim(animName, startWhenReady);
}

/**
 * @fn	void Entity::incSpeed(sf::Vector2f s)
 *
 * @brief	Increment speed.
 *
 * @param	s	The sf::Vector2f to process.
 */
void Entity::incSpeed(sf::Vector2f s)
{
	m_speed += s;
}


#pragma region get()

/**
 * @fn	sf::Vector2f Entity::getPosition()
 *
 * @brief	Gets the position.
 *
 * @return	The position.
 */
sf::Vector2f Entity::getPosition()
{
	return sf::Vector2f(m_box.left, m_box.top);
}

/**
 * @fn	float Entity::getHeight()
 *
 * @brief	Gets the height.
 *
 * @return	The height.
 */
float Entity::getHeight()
{
	return m_box.height;
}

/**
 * @fn	float Entity::getWidth()
 *
 * @brief	Gets the width.
 *
 * @return	The width.
 */
float Entity::getWidth()
{
	return m_box.width;
}

/**
 * @fn	sf::Vector2f Entity::getSpeed()
 *
 * @brief	Gets the speed.
 *
 * @return	The speed.
 */
sf::Vector2f Entity::getSpeed()
{
	return m_speed;
}

/**
 * @fn	int Entity::getWeight()
 *
 * @brief	Gets the weight.
 *
 * @return	The weight.
 */
int Entity::getWeight()
{
	return m_weight;
}

/**
 * @fn	sf::Rect<float> Entity::getBox()
 *
 * @brief	Gets the box.
 *
 * @return	The box.
 */
sf::Rect<float> Entity::getBox()
{
	return m_box;
}

#pragma endregion

#pragma region set()

/**
 * @fn	void Entity::setBox(float x, float y, float w, float h)
 *
 * @brief	Sets a box and relocate the animation at the same time.
 *
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @param	w	The width.
 * @param	h	The height.
 */
void Entity::setBox(float x, float y, float w, float h)
{
	m_box = sf::Rect<float>(x, y, w, h);
	m_animation->setPosition(x, y);
}

/**
 * @fn	void Entity::setBoxWithoutAnim(float x, float y, float w, float h)
 *
 * @brief	Sets box without moving the animation.
 *
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 * @param	w	The width.
 * @param	h	The height.
 */
void Entity::setBoxWithoutAnim(float x, float y, float w, float h)
{
	m_box = sf::Rect<float>(x, y, w, h);
}

/**
 * @fn	void Entity::setHeight(float h)
 *
 * @brief	Sets a height.
 *
 * @param	h	The height.
 */
void Entity::setHeight(float h)
{
	m_box.height = h;
}

/**
 * @fn	void Entity::setWidth(float w)
 *
 * @brief	Sets a width.
 *
 * @param	w	The width.
 */
void Entity::setWidth(float w)
{
	m_box.width = w;
}

/**
 * @fn	void Entity::setSpeed(sf::Vector2f s)
 *
 * @brief	Sets a speed.
 *
 * @param	s	The sf::Vector2f to process.
 */
void Entity::setSpeed(sf::Vector2f s)
{
	m_speed = s;
}

/**
 * @fn	void Entity::setAnimation(std::shared_ptr<Animation> anim)
 *
 * @brief	Sets an animation.
 *
 * @param	anim	The animation.
 */
void Entity::setAnimation(std::shared_ptr<Animation> anim)
{
	m_animation = anim;
}

/**
 * @fn	void Entity::setWeight(int w)
 *
 * @brief	Sets a weight.
 *
 * @param	w	The width.
 */
void Entity::setWeight(int w)
{
	m_weight = w;
}
#pragma endregion

#pragma endregion

/**
 * @fn	Entity::~Entity()
 *
 * @brief	Destructor.
 */

Entity::~Entity()
{

}
