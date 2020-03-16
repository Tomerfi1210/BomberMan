#pragma once
#include "MoveAble.h"
#include <functional>

enum Guard_Dir_t{Down_d, Left_d, Right_d, Up_d, Max_D};
class Guards : public MoveAble
{
public:
	Guards(const Object_t& obj, sf::Vector2f &pos);
	virtual ~Guards() = 0{};
	virtual void move(const Board &board) = 0;
	virtual void setRobot(Robot& robot) {};

	void SetDirctionGuard()
	{
		switch (m_dir)
		{
		case Right:
			m_step = { m_speed,  0 };
			break;
		case Down:
			m_step = { 0,  m_speed };
			break;
		case Up:
			m_step = { 0,  -m_speed };
			break;
		case Left:
			m_step = { -m_speed, 0 };
			break;
		default:
			break;
		}
		//	m_sprite.move(m_step);//TODO check if move is valid in the screen.
	}
	//--------------------collision double dispach----------------------------------
protected:	
	sf::Clock m_timeSGuard;
	sf::Clock m_timeD;
	sf::Time m_moveTimeS = sf::seconds((float)0.0019);
	sf::Time m_randTime = sf::seconds((float)0.5);
	bool Collide = false;
	Guard_Dir_t m_dirr;
};

