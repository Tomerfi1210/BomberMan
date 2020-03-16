#include "Bomb.h"
#include "Robot.h"
#include "SmartGuard.h"
#include "StupidGuard.h"
#include "Fire.h"


Bomb::Bomb(sf::Vector2f &pos) :GameObjects(pos), m_fireCreated(false), timeToExplode(0)
{
	m_texture = (Pictures::getInstance().getTexture(Bomb_type));
	m_sprite.setTexture(*m_texture);
	sf::IntRect bomb = { 0, 0 , PIC_SIZE, PIC_LENGTH };
	m_sprite.setTextureRect(bomb);
	m_sprite.setPosition({ pos.x + 5,pos.y + 5 });
	pos.x /= PIC_SIZE;
	pos.y /= PIC_SIZE;

	sf::Vector2i loc;
	loc = { (int)pos.x, (int)pos.y };
	m_fire.push_back(std::make_unique<Fire>(loc, Center));

	loc = { (int)pos.x + 1, (int)pos.y };
	m_fire.push_back(std::make_unique<Fire>(loc, Horizontal));

	loc = { (int)pos.x - 1, (int)pos.y };
	m_fire.push_back(std::make_unique<Fire>(loc, Horizontal));

	loc = { (int)pos.x, (int)pos.y - 1 };
	m_fire.push_back(std::make_unique<Fire>(loc, Vertical));

	loc = { (int)pos.x, (int)pos.y + 1 };
	m_fire.push_back(std::make_unique<Fire>(loc, Vertical));
}


Bomb::~Bomb()
{
}

bool Bomb::exploded()
{
	if (m_timeExploade.getElapsedTime().asSeconds() >= m_timeOver.asSeconds())
	{
		m_timeExploade.restart();
		m_fireCreated = true;
		return true;
	}
	return false;
}

bool Bomb::timeToClean()
{
	if (m_timeFire.getElapsedTime().asSeconds() >= m_timeOverFire.asSeconds())//when to erase the bomb from the vector.
	{
		m_timeFire.restart();
		m_fireCreated = false;
		return true;
	}
	return false;
		
}

void Bomb::fireDraw(sf::RenderWindow& window)
{
	for (auto& f : m_fire) {
		f->draw(window);
	}
	
}

void Bomb::draw(sf::RenderWindow &window)
{
	if (m_fireCreated)
	{
		fireDraw(window);
	}
	else{
		window.draw(m_sprite);
	}
}

void Bomb::increaseRadius()
{

}

bool Bomb::collideHandler(GameObjects & other)
{
	return false;
}

bool Bomb::collideHandler(Robot & other)
{
	for (size_t i = 0; i < m_fire.size(); i++) {
		if (m_fire[i]->collideHandler(other))
			return true;
	}
	return false;
}

bool Bomb::collideHandler(SmartGuard & other)
{
	for (size_t i = 0; i < m_fire.size(); i++) {
		if (m_fire[i]->collideHandler(other))
			return true;
	}
	return false;
}

bool Bomb::collideHandler(StupidGuard & other)
{
	for (size_t i = 0; i < m_fire.size(); i++) {
		if (m_fire[i]->collideHandler(other))
			return true;
	}
	return false;
}

bool Bomb::collideHandler(Rock & other)
{
	for (size_t i = 1; i < m_fire.size(); i++) 
	{
		if (m_fire[i]->collideHandler(other))
		{
			return true;
		}
	}
	return false;
}

bool Bomb::collideHandler(Wall & other)
{
	for (size_t i = 1; i < m_fire.size(); i++) {
		if (m_fire[i]->collideHandler(other))
			m_fire.erase(m_fire.begin() + i);
	}
	return false;
}

bool Bomb::collideHandler(Fire & other)
{
	return false;
}

bool Bomb::collideHandler(Bomb & other)
{
	return false;
}

bool Bomb::collideHandler(Lighting_Gift & other)
{
	return false;
}
