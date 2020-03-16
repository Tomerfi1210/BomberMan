#pragma once
#include "GameObjects.h"

enum Fire_t { Center, Horizontal, Vertical};
class Fire : public GameObjects
{
public:
	Fire(sf::Vector2i&, const Fire_t&);
	~Fire();
	void draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite); 
	}
	virtual bool isCollide(const sf::FloatRect& rect) const;

	virtual bool collideHandler(GameObjects& other);

	virtual bool collideHandler(Robot &other);
	virtual bool collideHandler(SmartGuard& other);
	virtual bool collideHandler(StupidGuard& other);
	virtual bool collideHandler(Rock& other);
	virtual bool collideHandler(Wall& other);
	virtual bool collideHandler(Fire& other);
	virtual bool collideHandler(Bomb& other);
	virtual bool collideHandler(Lighting_Gift& other) { return false; }
	virtual bool collideHandler(SpeedGift& other) { return false; }
	virtual bool collideHandler(BombGift& other) { return false; }

private:

};

