#pragma once
#include "UnMoveAble.h"

//---------------check-------//
class Door : public UnMoveAble
{
public:
	Door(sf::Vector2f &pos);
	~Door();


	virtual bool isCollide(const sf::FloatRect& rect) const;

	virtual bool collideHandler(GameObjects& other);

	virtual bool collideHandler(Robot &other);
	virtual bool collideHandler(SmartGuard& other);
	virtual bool collideHandler(StupidGuard& other);
	virtual bool collideHandler(Rock& other);
	virtual bool collideHandler(Wall& other);
	virtual bool collideHandler(Fire& other);
	virtual bool collideHandler(Bomb& other) { return false; }
	virtual bool collideHandler(Lighting_Gift& other) { return false; }
	virtual bool collideHandler(SpeedGift& other) { return false; }
	virtual bool collideHandler(BombGift& other) { return false; }

private:
	static bool m_registered;
};

