#pragma once
#include "GameObjects.h"

enum PowerUps_t { Bomb_t, Lightning_t, Speed_t };

class Gifts : public GameObjects
{
public:
	Gifts(sf::Vector2f&);
	Gifts() = default;
	void draw(sf::RenderWindow&);
	~Gifts();

protected:
	PowerUps_t m_type;
	sf::Clock m_timer;
	float m_change;
	int m_transparency;
	sf::Sprite m_background;
};

