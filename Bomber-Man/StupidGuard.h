#pragma once
#include "Guards.h"

class StupidGuard : public Guards
{
public:
	StupidGuard(sf::Vector2f &pos);
	virtual void move(const Board &board);
	~StupidGuard();

	virtual bool isCollide(const sf::FloatRect& rect) const;

	virtual bool collideHandler(GameObjects& other);

	virtual bool collideHandler(Robot &other);
	virtual bool collideHandler(SmartGuard& other) { return false; }
	virtual bool collideHandler(StupidGuard& other) { return false; }
	virtual bool collideHandler(Rock& other);
	virtual bool collideHandler(Wall& other);
	virtual bool collideHandler(Fire& other);
	virtual bool collideHandler(Bomb& other);
	virtual bool collideHandler(Lighting_Gift& other) { return false; }
	virtual bool collideHandler(SpeedGift& other) { return false; }
	virtual bool collideHandler(BombGift& other) { return false; }


private:
	static bool m_registered;
	
};

