#include "Fire.h"
#include "Robot.h"
#include "Rock.h"
#include "Wall.h"
#include "Door.h"
#include "StupidGuard.h"
#include "SmartGuard.h"

Fire::Fire(sf::Vector2i &bombPos, const Fire_t& dir)
{
	m_texture = (Pictures::getInstance().getTexture(Boom_type));
	m_sprite.setTexture(*m_texture);
	sf::IntRect tmp(dir * PIC_SIZE, 0, PIC_SIZE, PIC_SIZE);
	//m_sprite.setOrigin(PIC_SIZE / 2, PIC_SIZE / 2);
	m_sprite.setTextureRect(tmp);
	m_sprite.setPosition(bombPos.x*PIC_SIZE, bombPos.y*PIC_SIZE);
}

Fire::~Fire()
{
}

bool Fire::isCollide(const sf::FloatRect & rect) const
{
	if (m_sprite.getGlobalBounds().intersects(rect)) {
		std::cout << "Fire Vs Float rect" << std::endl;
		return true;
	}
	return false;
}

bool Fire::collideHandler(GameObjects & other)
{
	return other.collideHandler(*this);
}

bool Fire::collideHandler(Robot & other)
{
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool Fire::collideHandler(SmartGuard & other)
{
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool Fire::collideHandler(StupidGuard & other)
{
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool Fire::collideHandler(Rock & other)
{
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool Fire::collideHandler(Wall & other)
{
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool Fire::collideHandler(Fire & other)
{
	return false;
}

bool Fire::collideHandler(Bomb & other)
{
	return false;
}
