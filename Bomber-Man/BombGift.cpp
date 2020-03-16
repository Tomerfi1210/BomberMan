#include "BombGift.h"
#include "GiftFactory.h"

BombGift::BombGift(sf::Vector2f & pos) : Gifts(pos)
{
	m_type = Bomb_t;
}

BombGift::~BombGift()
{
}
bool BombGift::m_registered = GiftFactory::registerit(Bomb_Gift_c, [](sf::Vector2f &pos) -> std::unique_ptr<Gifts> { return std::make_unique< BombGift>(pos); });