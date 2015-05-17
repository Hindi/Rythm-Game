#include "Player.h"



#pragma region constructeurs

/**
 * @fn	Player::Player()
 *
 * @brief	Default constructor.
 *
 */
Player::Player() : Entity(), m_health(100)
{	
	init();
	//Décalage du aux à la partie transparentes des sprites
	setBoxWithoutAnim(m_box.left +14 , m_box.top + 36, 50, 50);

}

/**
 * @fn	Player::Player(float x, float y)
 *
 * @brief	Constructor.
 *
 * @param	x	The x coordinate.
 * @param	y	The y coordinate.
 */
Player::Player(float x, float y) : Entity(x, y), m_health(100)
{
	init();
	//Décalage du aux vides des sprites
	setBoxWithoutAnim(m_box.left + 14, m_box.top + 36, 50, 50);
}

/**
 * @fn	Player::Player(sf::Vector2f pos, float w, float h)
 *
 * @brief	Constructor.
 *
 * @param	pos	The position.
 * @param	w  	The width.
 * @param	h  	The height.
 */
Player::Player(sf::Vector2f pos, float w, float h) : Entity(pos, w, h), m_health(100)
{	
	init();
	//Décalage du aux vides des sprites
	setBoxWithoutAnim(m_box.left + 14, m_box.top + 36, 50, 50);
}

/**
 * @fn	Player::Player(sf::Vector2f pos, float w, float h, sf::Vector2f speed, int weight, std::shared_ptr<Animation> anim)
 *
 * @brief	Constructor.
 *
 * @param	pos   	The position.
 * @param	w	  	The width.
 * @param	h	  	The height.
 * @param	speed 	The speed.
 * @param	weight	The weight.
 * @param	anim  	The animation.
 */
Player::Player(sf::Vector2f pos, float w, float h, sf::Vector2f speed, int weight, std::shared_ptr<Animation> anim) : Entity(pos, w, h, speed, weight, anim), m_health(100)
{	
	init();
	//Décalage du aux vides des sprites
	setBoxWithoutAnim(m_box.left + 14, m_box.top + 36, 50, 50);
}

/**
 * @fn	void Player::init()
 *
 * @brief	Initialises this object.
 *
 */
void Player::init()
{
	createAnimation();
	m_jumpHeight = 150;
	m_jumping = false;
	m_crouching = false;
}

/**
 * @fn	void Player::createAnimation()
 *
 * @brief	Creates the animations.
 *
 */
void Player::createAnimation()
{
	m_animation = std::shared_ptr<Animation>(new Animation(100, false, false, 0.05f));

	//On charge l'image et on découpe toutes les animations dedans
	sf::Image m_image;
	m_image = MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/player.png");
	int imgSize{ 90 };//Taille de chaque image en pixel
	
	//quand on avance
	auto idleAnim = std::make_shared<Anim>("idle");
	idleAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));

	//Quand on saute
	auto jumpAnim = std::make_shared<Anim>("jump");
	jumpAnim->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, 0, imgSize, imgSize)));
	jumpAnim->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, imgSize, imgSize, imgSize)));

	//Quand on ralenti, en haut du saut
	auto onTop = std::make_shared<Anim>("onTop");
	onTop->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, 0, imgSize, imgSize)));
	onTop->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));

	//Quand on arrive en bas
	auto onBottom = std::make_shared<Anim>("onBottom");
	onBottom->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, 0, imgSize, imgSize)));
	onBottom->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));
	onBottom->pushFrame(Frame(m_image, sf::Rect<int>(2 * imgSize, 0, imgSize, imgSize)));
	onBottom->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));

	m_image = MediaManager<sf::Image>::getInstance().getMedia("../JIN4/media/PlayerCrouch.png");

	//Quand on se baisse
	auto crouchAnim = std::make_shared<Anim>("crouch");
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));
	//crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, 0, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, 0, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(2 * imgSize, 0, imgSize, imgSize)));
	//crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, imgSize, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, imgSize, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(imgSize, imgSize, imgSize, imgSize)));
	//crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(2 * imgSize, imgSize, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(2 * imgSize, imgSize, imgSize, imgSize)));
	crouchAnim->pushFrame(Frame(m_image, sf::Rect<int>(0, 0, imgSize, imgSize)));

	//On les rajoute à l'animation
	m_animation->addAnim("onBottom", onBottom);
	m_animation->addAnim("onTop", onTop);
	m_animation->addAnim("jump", jumpAnim);
	m_animation->addAnim("crouch", crouchAnim);
	m_animation->addAnim("idle", idleAnim);
	m_animation->setAnim("idle", true);

	AnimationManager::getInstance().addAnimation(m_animation);
	m_animation->setPosition(sf::Vector2f(m_box.left, m_box.top));
}

#pragma endregion

#pragma region methodes

/**
 * @fn	void Player::hit(unsigned int hp)
 *
 * @brief	When the player get hit, its hp reduce.
 *
 * @param	hp	The hp.
 */
void Player::hit(unsigned int hp)
{
	if (hp > m_health)
	{
		m_health = 0;
	}
	else
	{
		m_health -= hp;
	}
}

/**
 * @fn	void Player::jump()
 *
 * @brief	Check if the player can jump and then trigger the jump event and initialise the Player for the jump
 *
 */
void Player::jump()
{
	if (!m_jumping && !m_crouching)
	{
		EventManager<void>::getInstance().call("inAction");
		m_currentJumpState = JumpState::StartJump;
		m_animation->setAnim("jump", true);
		setSpeed(sf::Vector2f(0, -30));
		m_rollPosition = getPosition();
		m_jumping = true;
	}
}

/**
 * @fn	void Player::doJump()
 *
 * @brief	Called each frame by the Physic class to update the player when its jumping
 *
 */
void Player::doJump()
{
	switch (m_currentJumpState)
	{
	case JumpState::NotJumping:
		break;
	case JumpState::StartJump:
		if (m_rollPosition.y - m_box.top >= m_jumpHeight - m_jumpHeight / 3)
		{
			m_animation->setFrameTime(0.05f);
			setSpeed(sf::Vector2f(0, -15));
			m_animation->setAnim("onTop", true);
			m_currentJumpState = JumpState::ReachingTop;
		}
		break;
	case JumpState::ReachingTop:
		if (m_rollPosition.y - m_box.top >= m_jumpHeight)
		{
			setSpeed(sf::Vector2f(0, 15));
			m_animation->setAnim("jump", true);
			m_currentJumpState = JumpState::LeavingTop;
		}
		break;
	case JumpState::LeavingTop:

		if (m_rollPosition.y - m_box.top <= m_jumpHeight - m_jumpHeight / 3)
		{
			m_animation->setFrameTime(0.05f);
			setSpeed(sf::Vector2f(0, 30));
			m_currentJumpState = JumpState::FallingDown;
		}
		break;
	case JumpState::FallingDown:
		if (m_rollPosition.y - m_box.top < 0.1)
		{
			translate(m_rollPosition - getPosition());
			setSpeed(sf::Vector2f(0, 0));
			m_animation->setAnim("onBottom", true);
			m_currentJumpState = JumpState::Landing;
			m_jumping = false;
		}
		break;
	case JumpState::Landing:
		if (m_animation->hasended())
		{
			m_animation->setAnim("idle", true);
			m_currentJumpState = JumpState::NotJumping;
		}
		break;
	}
}

/**
 * @fn	void Player::crouch()
 *
 * @brief	Check if the player can crouch and then trigger the jump event and initialise the Player for the crouch
 *
 */
void Player::crouch()
{
	if (!m_jumping && !m_crouching)
	{
		EventManager<void>::getInstance().call("inAction");
		m_crouching = true;
		m_animation->setFrameTime(0.05f);
		m_box.top += 45;
		m_animation->setAnim("crouch", true);
	}
}

/**
* @fn	void Player::doCrouch()
*
* @brief	Called each frame by the Physic class to update the player when its crouching
*
* @author	Vincent
* @date	16/06/2014
*/
void Player::doCrouch()
{
	if (m_animation->hasended())
	{	
		m_box.top -= 45;
		m_crouching = false;
		m_animation->setAnim("idle", true);
	}
}


#pragma region set()

/**
 * @fn	void Player::setVerticalSpeed(float vs)
 *
 * @brief	Sets vertical speed.
 *
 *
 * @param	vs	The vs.
 */
void Player::setVerticalSpeed(float vs)
{
	m_speed.y = vs;
}

/**
 * @fn	void Player::setHealth(int h)
 *
 * @brief	Sets a health.
 *
 * @param	h	The height.
 */
void Player::setHealth(int h)
{
	m_health = h;
}
#pragma endregion

#pragma region get()

/**
 * @fn	int Player::getHealth()
 *
 * @brief	Gets the health.
 *
 * @return	The health.
 */
int Player::getHealth()
{
	return m_health;
}

/**
 * @fn	float Player::getVerticalSpeed()
 *
 * @brief	Gets vertical speed.
 *
 * @return	The vertical speed.
 */
float Player::getVerticalSpeed()
{
	return m_speed.y;
}

/**
 * @fn	bool Player::isJumping()
 *
 * @brief	Query if this object is jumping.
 *
 * @return	true if jumping, false if not.
 */
bool Player::isJumping()
{
	return m_jumping;
}

/**
 * @fn	bool Player::isCrouching()
 *
 * @brief	Query if this object is crouching.
 *
 * @return	true if crouching, false if not.
 */
bool Player::isCrouching()
{
	return m_crouching;
}

#pragma endregion

#pragma endregion

/**
 * @fn	Player::~Player()
 *
 * @brief	Destructor.
 *
 */
Player::~Player()
{
}