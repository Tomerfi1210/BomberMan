#pragma once
#include "Board.h"
#include "Gifts.h"

const int LEVELS = 3;
class Controller
{
public:
	Controller();
	void run(sf::RenderWindow &m_window);
	~Controller();

private:
	vector<std::unique_ptr<Guards>> m_guards;//hold guards.
	vector<std::unique_ptr<UnMoveAble>>m_staticBoard;//holds wall and rock.
	vector<std::unique_ptr<Bomb>>m_bombs;//holds bombs of the player.
	vector<std::unique_ptr<Gifts>>m_gifts;//holds gifts on board.

	void newLevel(sf::RenderWindow &);
	void resetLevel(sf::RenderWindow &m_window);
	void drawSide(sf::RenderWindow& m_window);
	void eraseBombs();
	std::unique_ptr<Robot> m_robot;
	Board *m_board;
	void handleEvents(sf::RenderWindow &m_window,sf::Event &event);
	void collides(sf::RenderWindow&);
	void drawBackGround(sf::RenderWindow &);
	void movePlayers();
	void printBoard(sf::RenderWindow&);
	void setBomb();
	void checkExploded(sf::RenderWindow&);
	float m_timer;
	bool explode = false;
	sf::Vector2f getPosOn(sf::Vector2f&);
	void stopGift();
	void handleText(sf::RenderWindow &m_window, const sf::String &name,
		const sf::Vector2f &pos);
	void handleValues(sf::RenderWindow &m_window, const int &value,
		const sf::Vector2f &pos);
	bool isStop = false;
	int m_currLvl = 0;
	int m_score = 0;
};

