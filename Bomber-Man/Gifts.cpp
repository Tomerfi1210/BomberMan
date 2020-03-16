#include "Gifts.h"

Gifts::Gifts(sf::Vector2f& location) : GameObjects(location), m_change(0), m_transparency(0)
{
	m_texture = (Pictures::getInstance().getTexture(Gifts_type));
	m_sprite.setTexture(*m_texture);
	m_background.setTexture(*Pictures::getInstance().getTexture(Back_gift_type));
	m_sprite.setPosition(location.x, location.y);
}


void Gifts::draw(sf::RenderWindow &window)
{
	m_background.setPosition(m_sprite.getPosition());
	m_sprite.setTextureRect(sf::IntRect(0, m_type*PIC_SIZE, PIC_SIZE, PIC_SIZE));
	m_change += m_timer.restart().asSeconds();

	if (m_change > 0.001)
	{
		m_transparency++;
		m_background.setColor(sf::Color(255, 255, 255, m_transparency));
		m_change = 0;

	}

	window.draw(m_background);
	window.draw(m_sprite);
}


Gifts::~Gifts()
{
}
