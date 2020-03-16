#include "SpeedGift.h"
#include "GiftFactory.h"
#include "Robot.h"



SpeedGift::SpeedGift(sf::Vector2f& pos) : Gifts(pos)
{
	m_type = Speed_t;
}

bool SpeedGift::collideHandler(Robot & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds()))
	{
		other.collideHandler(*this);
		return true;
	}
	return false;
}


SpeedGift::~SpeedGift()
{
}
bool SpeedGift::m_registered = GiftFactory::registerit(Speed_c, [](sf::Vector2f &pos) -> std::unique_ptr<Gifts> { return std::make_unique<SpeedGift>(pos); });