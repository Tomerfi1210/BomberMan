#pragma once
#include "Gifts.h"
class SpeedGift : public Gifts
{
public:
	~SpeedGift();
	SpeedGift(sf::Vector2f& pos);


	virtual bool isCollide(const sf::FloatRect& rect)const { return false; }

	virtual bool collideHandler(GameObjects& other) { return false; }

	virtual bool collideHandler(Robot &other);
	virtual bool collideHandler(SmartGuard& other) { return false; }
	virtual bool collideHandler(StupidGuard& other) { return false; }
	virtual bool collideHandler(Rock& other) { return false; }
	virtual bool collideHandler(Wall& other) { return false; }
	virtual bool collideHandler(Fire& other) { return false; }
	virtual bool collideHandler(Bomb& other) { return false; }
	virtual bool collideHandler(Lighting_Gift& other) { return false; }
	virtual bool collideHandler(SpeedGift& other) { return false; }
	virtual bool collideHandler(BombGift& other) { return false; }

private:
	static bool m_registered;
};

