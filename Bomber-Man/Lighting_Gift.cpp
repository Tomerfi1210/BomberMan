#include "Lighting_Gift.h"
#include "Robot.h"
#include "GiftFactory.h"

Lighting_Gift::Lighting_Gift(sf::Vector2f & pos) : Gifts(pos)
{
	m_type = Lightning_t;
}

Lighting_Gift::~Lighting_Gift()
{
}
bool Lighting_Gift::collideHandler(Robot & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds()))
	{
		other.collideHandler(*this);
		return true;
	}
	return false;
}
bool Lighting_Gift::m_registered = GiftFactory::registerit(Lighting_c, [](sf::Vector2f &pos) -> std::unique_ptr<Gifts> { return std::make_unique< Lighting_Gift>(pos); });