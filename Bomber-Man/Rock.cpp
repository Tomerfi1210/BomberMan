#include "Rock.h"
#include "Robot.h"
#include "Bomb.h"
#include "SmartGuard.h"
#include "StupidGuard.h"
#include "Fire.h"
#include "ObjectFactory.h"


Rock::Rock(sf::Vector2f &pos) : UnMoveAble(pos)
{
	m_texture = (Pictures::getInstance().getTexture(Rock_type));
	m_sprite.setTexture(*m_texture);
	sf::IntRect rock(PIC_SIZE, 0, PIC_SIZE, PIC_SIZE);
	m_sprite.setTextureRect(rock);
}


Rock::~Rock()
{
}
bool Rock::isCollide(const sf::FloatRect & rect) const
{
	return m_sprite.getGlobalBounds().intersects(rect);
}
//------------------------------------------------------------
bool Rock::collideHandler(GameObjects & other)
{
	return other.collideHandler(*this);
}
//--------------------------------------------------------
bool Rock::collideHandler(Robot & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds())) 
		return other.collideHandler(*this);
}
//-------------------------------------------------------------
bool Rock::collideHandler(SmartGuard & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds()))
		return other.collideHandler(*this);
}
//-----------------------------------------------------------------
bool Rock::collideHandler(StupidGuard & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds()))
		return other.collideHandler(*this);
}
//------------------------------------------------------------------
bool Rock::collideHandler(Fire & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds())) {
		std::cout << "Rock vs Fire" << std::endl;
		other.isCollide(m_sprite.getGlobalBounds());
		return false;
	}
	return false;
}
//----------------------------------------------------------------
bool Rock::collideHandler(Bomb & other)
{
	return other.collideHandler(*this);
}
//---------------------------------------------------------
bool Rock::m_registered = ObjectFactory::registerit(Rock_c, [](sf::Vector2f &place) -> std::unique_ptr<UnMoveAble> { return std::make_unique<Rock>(place); });