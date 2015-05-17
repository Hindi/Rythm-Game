#include "Anim.h"

/**
 * @fn	Anim::Anim()
 *
 * @brief	Default constructor.
 *
 */
Anim::Anim()
{

}

/**
* @fn	Anim::Anim()
*
* @brief	Constructor wth Anim's name.
*
*/
Anim::Anim(std::string name)
{
	m_name = name;
}

/**
 * @fn	Anim::~Anim()
 *
 * @brief	Destructor.
 *
 */
Anim::~Anim()
{

}

/**
 * @fn	Anim::Anim(const Anim& Cpy)
 *
 * @brief	Copy constructor.
 *
 *
 * @param	Cpy	The copy.
 */
Anim::Anim(const Anim& Cpy)
{
	m_frame = Cpy.m_frame;
	m_name = Cpy.m_name;
}

/**
 * @fn	void Anim::pushFrame(const Frame& NewFrame)
 *
 * @brief	Pushes a new frame.
 *
 * @param	NewFrame	The new frame.
 */
void Anim::pushFrame(const Frame& NewFrame)
{
    m_frame.push_back(NewFrame);
}

/**
 * @fn	size_t Anim::size() const
 *
 * @brief	Gets the number of frame stored.
 *
 * @return	A size_t.
 */
size_t Anim::size() const
{
    return m_frame.size();
}

/**
 * @fn	Frame& Anim::operator[] (size_t N)
 *
 * @brief	Array indexer operator.
 *
 * @param	N	The size_t to process.
 *
 * @return	The indexed value.
 */
Frame& Anim::operator [] (size_t N)
{
	return m_frame[N];
}

/**
 * @fn	Frame& Anim::getFrame(size_t N)
 *
 * @brief	Gets the number "N" frame.
 *
 * @param	N	The number of the frame.
 *
 * @return	The frame.
 */
Frame& Anim::getFrame(size_t N)
{
	return m_frame[N];
}

bool Anim::isLastFrame(int frameNumber)
{
	return (frameNumber == m_frame.size() - 1);
}

/**
 * @fn	void Anim::reset()
 *
 * @brief	Resets this anim.
 *
 */
void Anim::reset()
{
    m_frame.clear();
}

/**
 * @fn	void Anim::setName(std::string name)
 *
 * @brief	Sets a name.
 *
 * @param	name	The name.
 */
void Anim::setName(std::string name)
{
	m_name = name;
}

/**
 * @fn	std::string Anim::getName() const
 *
 * @brief	Gets the name.
 *
 * @return	The name.
 */
std::string Anim::getName() const
{
	return m_name;
}

/**
 * @fn	bool Anim::operator== (const Anim& anim)
 *
 * @brief	Equality operator.
 *
 * @param	anim	The animation.
 *
 * @return	true if the parameters are considered equivalent.
 */
bool Anim::operator == (const Anim& anim)
{
	return (m_name == anim.getName());
}