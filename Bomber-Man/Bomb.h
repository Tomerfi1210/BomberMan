#pragma once
#include "GameObjects.h"


class Bomb : public GameObjects
{
public:
	Bomb(sf::Vector2f &pos);
	~Bomb();
	bool exploded();
	bool timeToClean();
	void fireDraw(sf::RenderWindow& window);
	void draw(sf::RenderWindow&);
	bool fireIsCreate() const { return m_fireCreated; }
	void increaseRadius();
	////TODO collides
	virtual bool isCollide(const sf::FloatRect& rect) const { return m_sprite.getGlobalBounds().intersects(rect); }

	virtual bool collideHandler(GameObjects& other);

	virtual bool collideHandler(Robot &other);
	virtual bool collideHandler(SmartGuard& other);
	virtual bool collideHandler(StupidGuard& other);
	virtual bool collideHandler(Rock& other);
	virtual bool collideHandler(Wall& other);
	virtual bool collideHandler(Fire& other);
	virtual bool collideHandler(Bomb& other);
	virtual bool collideHandler(Lighting_Gift& other);
	virtual bool collideHandler(SpeedGift& other) { return false; }
	virtual bool collideHandler(BombGift& other) { return false; }
		

private:
	sf::Clock m_timeExploade;
	sf::Clock m_timeFire;
	sf::Time m_timeOver = sf::seconds(4.f);
	sf::Time m_timeOverFire = sf::seconds(6.f);
	vector<std::unique_ptr<Fire>> m_fire;
	float timeToExplode;
	bool m_fireCreated;
	sf::Vector2i m_location;
};