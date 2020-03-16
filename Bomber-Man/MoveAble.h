#pragma once
#include "GameObjects.h"
#include "ObjectFactory.h"

class MoveAble : public GameObjects
{
public:
	MoveAble(sf::Vector2f &pos);
	MoveAble() = delete;
	virtual ~MoveAble() = 0 {};
	virtual void move(const Board &board) = 0 ;
	//---------------------------------------
  
protected:
	float m_speed;
	int m_stepCount;
	sf::Vector2f m_step;
	int m_move;
	
};

