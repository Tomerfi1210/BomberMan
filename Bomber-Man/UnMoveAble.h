#pragma once
#include "GameObjects.h"
class UnMoveAble : public GameObjects
{
public:
	UnMoveAble(sf::Vector2f &place);
	UnMoveAble()=default;
	virtual ~UnMoveAble() = 0 {};
	virtual void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
protected:

};

