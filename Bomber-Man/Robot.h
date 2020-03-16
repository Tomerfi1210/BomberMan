#pragma once
#include "MoveAble.h"
#include <functional>

//----check----//
class Robot : public MoveAble
{
public:
	Robot(sf::Vector2f &pos);
	virtual ~Robot();
	virtual void move(const Board &board) override;
	sf::Vector2f getrobotCenter()const;
	//----------------Double Dispatch--------------------
	virtual bool isCollide(const sf::FloatRect& rect) const;
	virtual bool collideHandler(GameObjects& other);
	virtual bool collideHandler(Robot &other) { return false; }
	virtual bool collideHandler(SmartGuard& other);
	virtual bool collideHandler(StupidGuard& other);
	virtual bool collideHandler(Rock& other);
	virtual bool collideHandler(Wall& other);
	virtual bool collideHandler(Fire& other);
	virtual bool collideHandler(Bomb& other);
	virtual bool collideHandler(Lighting_Gift& other) { return true;; }
	virtual bool collideHandler(SpeedGift& other);
	virtual bool collideHandler(BombGift& other) { return true; }

	void setBombs(const int& amountbombs) { m_bombs = amountbombs; }
	void bombCounterDown() {m_bombs--;}
	int getCountBombs() const;
	void setDirection(const sf::Event &event);
	void setStep(const sf::Vector2f&) { m_sprite.move(m_step); }
	void gotHurt() { m_life--; }
	void increaseSpeed() 
	{ 
		m_speed *= 1.3f; 
		if (m_speed >= 1.7f)
			m_speed = 1.4f;
	}//for gifts.
	
	int getLife() const { return m_life; }
	int getScore() const { return m_score; }
	void increasScore() { m_score += 5; }
	void setScore(const int &score) { m_score += score; };

private:
	int m_life;
	int m_score = 0;
	int m_bombs = 52;
	bool m_moveHands = false;
	sf::Time m_moveTimer = sf::seconds(0.2f);
	sf::Clock m_timer;
	std::map < sf::Keyboard::Key, std::function<void(void)>> m_moves;//holds direction of the robot.
	vector<std::unique_ptr<Bomb>>m_playerBombs;
};

