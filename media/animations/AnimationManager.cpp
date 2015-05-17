#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	EventManager<void>::getInstance().addListener("death", std::bind(&AnimationManager::reset, this));
}

// Destructeur
AnimationManager::~AnimationManager()
{

}

/**
 * @fn	AnimationManager& AnimationManager::getInstance()
 *
 * @brief	Gets the instance of the singleton.
 *
 * @return	The instance.
 */
AnimationManager& AnimationManager::getInstance()
{
	static AnimationManager _singleton;
	return _singleton;
}

/**
 * @fn	bool compAnimation(std::shared_ptr<Animation> anim, std::shared_ptr<Animation>anim2)
 *
 * @brief	Free function used to sort the animations to draw them using a z-index.
 *
 * @param	anim	  	The animation.
 * @param	parameter2	The second parameter.
 *
 * @return	true if it succeeds, false if it fails.
 */
bool compAnimation(std::shared_ptr<Animation> anim, std::shared_ptr<Animation>anim2)
{
	return (anim->zIndex() < anim2->zIndex());
}

/**
 * @fn	std::shared_ptr<Animation> AnimationManager::addAnimation(std::shared_ptr<Animation> Cpy)
 *
 * @brief	Adds an animation.
 *
 * @param	Cpy	The copy.
 *
 * @return	A std::shared_ptr&lt;Animation&gt;
 */
std::shared_ptr<Animation> AnimationManager::addAnimation(std::shared_ptr<Animation> Cpy)
{
	m_animations.push_back(Cpy);
	std::sort(m_animations.begin(), m_animations.end(), compAnimation);

	return Cpy;
}

/**
 * @fn	std::shared_ptr<Animation> AnimationManager::addAnimation(bool Play, bool Loop, float Time)
 *
 * @brief	Adds an animation.
 *
 * @param	Play	true to play.
 * @param	Loop	true to loop.
 * @param	Time	The time.
 *
 * @return	A std::shared_ptr&lt;Animation&gt;
 */
std::shared_ptr<Animation> AnimationManager::addAnimation(bool Play, bool Loop, float Time)
{
	std::shared_ptr<Animation> animation(new Animation(Play, Loop, Time));
	m_animations.push_back(animation);
	std::sort(m_animations.begin(), m_animations.end(), compAnimation);

	return animation;
}

/**
 * @fn	void AnimationManager::addAnim(std::shared_ptr<Animation> animation, std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name)
 *
 * @brief	Adds an animation.
 *
 * @param	animation			The animation.
 * @param [in,out]	filename	Filename of the file.
 * @param	rects				The rectangles.
 * @param [in,out]	name		The name.
 */
void AnimationManager::addAnim(std::shared_ptr<Animation> animation, std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name)
{
	std::shared_ptr<Anim> anim = createAnim(filename, rects, name);

	animation->addAnim(name, anim);
}

/**
 * @fn	void AnimationManager::addAnim(std::shared_ptr<Animation> animation, const char filename[], std::vector< sf::Rect<int> > rects, const char name[])
 *
 * @brief	Adds an animation.
 *
 * @param	animation	The animation.
 * @param	filename 	Filename of the file.
 * @param	rects	 	The rectangles.
 * @param	name	 	The name.
 */
void AnimationManager::addAnim(std::shared_ptr<Animation> animation, const char filename[], std::vector< sf::Rect<int> > rects, const char name[])
{
	//Convertion const char to string
	std::string stringFilename( filename, strlen(filename));
	std::string stringName( name, strlen(name));

	std::shared_ptr<Anim> anim = createAnim(stringFilename, rects, stringName);

	animation->addAnim(name, anim);
}

/**
 * @fn	std::shared_ptr<Anim> AnimationManager::createAnim(std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name)
 *
 * @brief	Creates an animation but do not add it for update & draw.
 *
 * @param [in,out]	filename	Filename of the file.
 * @param	rects				The rectangles.
 * @param [in,out]	name		The name.
 *
 * @return	The new animation.
 */
std::shared_ptr<Anim> AnimationManager::createAnim(std::string& filename, std::vector< sf::Rect<int> > rects, std::string& name)
{
	sf::Image image;
	image = MediaManager<sf::Image>::getInstance().getMedia(filename);

	std::shared_ptr<Anim> anim;

	std::vector< sf::Rect<int> >::iterator it(rects.begin());
	for(; it != rects.end(); it++)
	{
		anim->pushFrame(Frame(image, *(it)));
	}

	return anim;
}

/**
 * @fn	Anim* createAnim(const char filename[], std::vector< sf::Rect<int> > rects, const char name[])
 *
 * @brief	Creates an animation but do not add it for update & draw.
 *
 * @param	filename	Filename of the file.
 * @param	rects   	The rectangles.
 * @param	name		The name.
 *
 * @return	null if it fails, else the new animation.
 */
Anim* createAnim(const char filename[], std::vector< sf::Rect<int> > rects, const char name[])
{
	sf::Image image;
	image = MediaManager<sf::Image>::getInstance().getMedia(filename);

	Anim* anim;
	anim = new Anim;

	std::vector< sf::Rect<int> >::iterator it(rects.begin());
	for(; it != rects.end(); it++)
	{
		anim->pushFrame(Frame(image, *(it)));
	}

	return anim;
}

/**
 * @fn	void AnimationManager::updateAnimation(sf::RenderWindow& window, bool paused)
 *
 * @brief	Updates the animations and draw them.

 *
 * @param [in,out]	window	The window.
 * @param	paused		  	true if paused.
 */
void AnimationManager::updateAnimation(sf::RenderWindow& window, bool paused)
{
	std::vector<std::shared_ptr<Animation> >::iterator it(m_animations.begin());
	for(; it != m_animations.end(); it++)
	{
		if((*it)->isDrawable())
		{
			if (!paused)
				(*it)->anim(clock.getElapsedTime().asSeconds());
			window.draw(**it);
		}
	}
	clock.restart();
}



void AnimationManager::reset()
{
	clock.restart();
}