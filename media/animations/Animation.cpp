#include "Animation.h"

/**
 * @fn	Animation::Animation(const Animation& Cpy) : sf::Sprite(Cpy)
 *
 * @brief	Copy constructor.
 *
 * @param	Cpy	The copy.
 */
Animation::Animation(const Animation& Cpy) :
sf::Sprite(Cpy)
{
    m_currentFrame = Cpy.m_currentFrame;
    m_time = Cpy.m_time;
    m_elapsedTime = Cpy.m_elapsedTime;
    Paused = Cpy.Paused;
    m_anim = Cpy.m_anim;
    m_loop = Cpy.m_loop;
	m_drawable = Cpy.m_drawable;

	for (auto it = Cpy.m_animations.begin(); it != Cpy.m_animations.end();)
	{
		m_animations[it->first] = it->second;
	}
}

/**
 * @fn	Animation::Animation(int zIndex, bool Play, bool Loop, float Time)
 *
 * @brief	Constructor.
 *
 * @param	zIndex	The index.
 * @param	Play  	true to play.
 * @param	Loop  	true to loop.
 * @param	Time  	The time.
 */
Animation::Animation(int zIndex, bool Play, bool Loop, float Time)
{
    m_anim = NULL;
    m_currentFrame = 0;
    m_time = Time;
    m_elapsedTime = Time;
    Paused = !Play;
    m_loop = Loop;
	m_drawable = true;
	m_zIndex = zIndex;
}

/**
 * @fn	Animation::Animation(std::shared_ptr<Anim> NewAnim, int zIndex, bool Play, bool Loop, float Time)
 *
 * @brief	Constructor.
 *
 * @param	NewAnim	The new animation.
 * @param	zIndex 	The index.
 * @param	Play   	true to play.
 * @param	Loop   	true to loop.
 * @param	Time   	The time.
 */
Animation::Animation(std::shared_ptr<Anim> NewAnim, int zIndex, bool Play, bool Loop, float Time)
{
    m_time = Time;
    m_elapsedTime = Time;
    Paused = !Play;
    m_loop = Loop;
    m_anim = NewAnim;
	m_drawable = true;
	m_zIndex = zIndex;

    setFrame(0);
}

// Destructeur
Animation::~Animation()
{

}

/**
 * @fn	void Animation::setAnim(std::shared_ptr<Anim> NewAnim)
 *
 * @brief	Sets an anim that is not stored in the animation active.
 *
 * @param	NewAnim	The new anim.
 */
void Animation::setAnim(std::shared_ptr<Anim> NewAnim)
{
    m_anim = NewAnim;

    setFrame(0);
}

/**
 * @fn	std::shared_ptr<Anim> Animation::getAnim()
 *
 * @brief	Gets the current anim.
 *
 * @return	The animation.
 */
std::shared_ptr<Anim> Animation::getAnim()
{
    return m_anim;
}

/**
 * @fn	void Animation::setFrame(int Frame)
 *
 * @brief	Assert before doSetFrame.
 *
 * @param	Frame	The frame.
 */

void Animation::setFrame(int Frame)
{
	assert(m_anim != NULL);
	assert(m_anim->size() >= Frame);
	doSetFrame(Frame);
}

/**
 * @fn	void Animation::doSetFrame(int Frame)
 *
 * @brief	Set the anim at the frame "frame".
 *
 * @param	Frame	The frame.
 */
void Animation::doSetFrame(int Frame)
{
	setTexture((*m_anim)[Frame].getTexture());

	m_currentFrame = Frame;
}

/**
 * @fn	int Animation::getCurrentFrame()
 *
 * @brief	Gets current frame.
 *
 * @return	The current frame.
 */
int Animation::getCurrentFrame()
{
    return m_currentFrame;
}

/**
 * @fn	void Animation::setFrameTime(float Time)
 *
 * @brief	Sets the time between each frame which define the speed of the animation.
 *
 * @param	Time	The time.
 */
void Animation::setFrameTime(float Time)
{
    m_time = Time;
}

/**
 * @fn	float Animation::getFrameTime()
 *
 * @brief	Get the time between each frame which define the speed of the animation.
 *
 * @return	The frame time.
 */
float Animation::getFrameTime()
{
    return m_time;
}

/**
 * @fn	void Animation::setLoop(bool Loop)
 *
 * @brief	Make the animation going on a loop or not.
 *
 * @param	Loop	true to loop.
 */
void Animation::setLoop(bool Loop)
{
    m_loop = Loop;
}

/**
 * @fn	bool Animation::isLoop()
 *
 * @brief	Query if this animation is goign on a loop.
 *
 * @return	true if loop, false if not.
 */
bool Animation::isLoop()
{
    return m_loop;
}

/**
 * @fn	void Animation::pause()
 *
 * @brief	Pauses this animation.
 * 			
 */
void Animation::pause()
{
    Paused = true;
}

/**
 * @fn	void Animation::play()
 *
 * @brief	Plays the animation.
 *
 */
void Animation::play()
{
    Paused = false;
}

/**
 * @fn	void Animation::stop()
 *
 * @brief	Stops this object (pause and rewind).
 *
 */
void Animation::stop()
{
    setFrame(0);
    m_elapsedTime = m_time;
    Paused = true;
}

/**
 * @fn	bool Animation::isPaused()
 *
 * @brief	Query if this object is paused.
 *
 * @return	true if paused, false if not.
 */
bool Animation::isPaused()
{
    return Paused;
}

/**
 * @fn	bool Animation::isStoped()
 *
 * @brief	Query if this object is stoped.
 *
 * @return	true if stoped, false if not.
 */
bool Animation::isStoped()
{
    return (Paused && (m_currentFrame == 0) && (m_elapsedTime == m_time));
}

/**
 * @fn	bool Animation::hasended()
 *
 * @brief	Query if the animation is finished.
 *
 * @return	true if it is, false if it's not.
 */
bool Animation::hasended()
{
	return(!isLoop() && m_anim->isLastFrame(m_currentFrame));
}

/**
 * @fn	void Animation::anim(float ElapsedTime)
 *
 * @brief	Assert before the animation operation.
 *
 * @param	ElapsedTime	The time elapsed since last doAnim.
 */
void Animation::anim(float ElapsedTime)
{
	assert(m_anim != NULL);
	doAnim(ElapsedTime);
}


/**
 * @fn	void Animation::doAnim(float ElapsedTime)
 *
 * @brief	Executes the animation operation.
 *
 * @param	ElapsedTime	The time elapsed since last doAnim.
 */
void Animation::doAnim(float ElapsedTime)
{
    // Si il n'est pas en pause et que l'animation est valide
    if (!Paused)
    {
        // on retranche le temps écoulé a notre compteur
        m_elapsedTime -= ElapsedTime;
		
        // Si Le temps entre chaque frame est atteint
        if (m_elapsedTime <= 0.f)
        {
            // On réinitialise notre compteur
            m_elapsedTime = m_time;
			
            // On passe a la frame suivante
            if (m_currentFrame + 1 < m_anim->size())
                m_currentFrame++;
            else
            {
                // Ou à la premiere
                if (m_loop)
                    m_currentFrame = 0;
                else
                {
                    // Si le mode Loop est désactivé, on stop l'animation
                    pause();
                }
			}

            // On change la frame
            setFrame(m_currentFrame);
        }
    }
}

/**
 * @fn	bool Animation::isStored(std::string const &name) const
 *
 * @brief	Query if an animation named 'name' is stored.
 *
 * @param	name	The name.
 *
 * @return	true if stored, false if not.
 */
bool Animation::isStored(std::string const &name) const
{
	//On vérifie que l'animation n'existe pas déjà
	for(auto it = m_animations.begin(); it != m_animations.end(); ++it)
	{
		if(name == it->first)
			return true;
	}
	return false;
}

/**
 * @fn	void Animation::addAnim(std::string const &name, std::shared_ptr<Anim> newAnim)
 *
 * @brief	Adds an animation to m_animations
 *
 * @param	name   	The name.
 * @param	newAnim	The new animation.
 */
void Animation::addAnim(std::string const &name, std::shared_ptr<Anim> newAnim)
{
	if (!isStored(name))
		m_animations[name] = newAnim;
	else
		std::cout << "DEBUG: " << "Anim " << name << " | déjà stocké dans l'animation" << std::endl;
}

/**
 * @fn	void Animation::setAnim(std::string const &animName, bool startWhenReady)
 *
 * @brief	Define the selected anim as active.
 *
 * @param	animName	  	Name of the animation.
 * @param	startWhenReady	true to start when ready.
 */
void Animation::setAnim(std::string const &animName, bool startWhenReady)
{
	if(isStored(animName))
	{
		m_anim = m_animations[animName];
		stop();
        setFrame(0);
		if (startWhenReady)
			play();
	}
	else
		std::cout << "DEBUG: " << animName << " | l'animation ne contient pas cette anim." << std::endl;
}

/**
 * @fn	void Animation::setDrawable(bool draw)
 *
 * @brief	Sets the animation drawable or not.
 *
 * @param	draw	true to draw.
 */
void Animation::setDrawable(bool draw)
{
	m_drawable = draw;
}

/**
 * @fn	bool Animation::isDrawable()
 *
 * @brief	Query if this object is drawable.
 *
 * @return	true if drawable, false if not.
 */
bool Animation::isDrawable()
{
	return m_drawable;
}

/**
 * @fn	int Animation::size() const
 *
 * @brief	Gets the size of m_animations
 *
 * @return	An int.
 */
int Animation::size() const
{
	return m_animations.size();
}

/**
 * @fn	int Animation::zIndex() const
 *
 * @brief	Gets the index.
 *
 * @return	m_zIndex
 */
int Animation::zIndex() const
{
	return m_zIndex;
}

/**
 * @fn	bool Animation::operator== (const Animation& anim)
 *
 * @brief	Equality operator.
 *
 * @param	anim	The animation.
 *
 * @return	true if the parameters are considered equivalent.
 */
bool Animation::operator == (const Animation& anim)
{
	for (auto &a : m_animations)
	{
		if (!anim.isStored(a.first))
			return false;
	}
	return true;
}

