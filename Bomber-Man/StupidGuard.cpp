#include "StupidGuard.h"
#include "Bomb.h"
#include "DynamicFactory.h"
#include "Robot.h"
#include "Rock.h"
#include "Fire.h"
#include "Wall.h"

StupidGuard::StupidGuard(sf::Vector2f &pos) : Guards(StupidGuard_type,pos)
{
	m_dirr = Right_d;
}

void StupidGuard::move(const Board & board)
{
	if (m_timeSGuard.getElapsedTime().asSeconds() >= m_moveTimeS.asSeconds())//enter every time guard need to move.
	{
		if (m_timeD.getElapsedTime().asSeconds() >= m_randTime.asSeconds())//enter every time guard need to change direction.
		{
			m_dir = (Direction_t)(rand() % Max_D);
			SetDirctionGuard();
			m_timeD.restart();
		}
		if (Collide)
		{
			m_dir = (Direction_t)(rand() % Max_D);
			SetDirctionGuard();
			Collide = false;
		}
		sf::IntRect tmp(PLAYER_WIDTH * m_stepCount, m_dir * PLAYER_WIDTH, PLAYER_WIDTH, PLAYER_WIDTH);
		m_sprite.setTextureRect(tmp);
		m_sprite.move(m_step);//TODO check if move is valid in the screen.

		m_stepCount++;
		m_timeSGuard.restart();
	}
	if (m_stepCount >= 3)
		m_stepCount = 0;
}


StupidGuard::~StupidGuard()
{
}
bool StupidGuard::isCollide(const sf::FloatRect & rect) const
{
	sf::FloatRect temp = { rect.left - 1, rect.top - 2, rect.width - 2, rect.height - 2 };
	//in order to check the next move
	sf::FloatRect newRec = { m_sprite.getGlobalBounds().left + m_step.x - 1,
							m_sprite.getGlobalBounds().top + m_step.y,
							m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height };
	if (newRec.intersects(temp))
	{
		return true;

	}
	return false;
}
//---------------------------------------------------------
bool StupidGuard::collideHandler(GameObjects & other)
{
	return other.collideHandler(*this);
}
//---------------------------------------------------------
bool StupidGuard::collideHandler(Robot & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds())) {
		std::cout << "StupidGuard vs Robot" << std::endl;
		return true;
	}
	return false;
}
//---------------------------------------------------------
bool StupidGuard::collideHandler(Rock & other)
{
	Collide = true;
	return other.isCollide(m_sprite.getGlobalBounds());
}
//---------------------------------------------------------
bool StupidGuard::collideHandler(Wall & other)
{
	Collide = true;
	return other.isCollide(m_sprite.getGlobalBounds());
}
//-----------------------------------------------------------
bool StupidGuard::collideHandler(Fire & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds())) {
		std::cout << "StupidGuard vs Fire" << std::endl;
		return true;
	}
	return false;
}
bool StupidGuard::collideHandler(Bomb & other)
{
	return other.collideHandler(*this);
}
//---------------------------------------------------------

bool StupidGuard::m_registered = DynamicFactory::registerit(Stupid_Guard_c, [](sf::Vector2f &pos) -> std::unique_ptr<Guards> { return std::make_unique< StupidGuard>(pos); });