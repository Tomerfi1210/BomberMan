#pragma once
#include "Robot.h"
#include "SmartGuard.h"
#include "StupidGuard.h"
#include "Wall.h"
#include "Door.h"
#include "Rock.h"
#include <fstream>
#include <string>

using std::ifstream;
//------Check-----------//
class Board
{
public:
	Board();
	~Board();
	bool readFile(vector<std::unique_ptr<Guards>> &, vector<std::unique_ptr<UnMoveAble>> &staticBoard,
				  std::unique_ptr<Robot>&robot, int col);
	sf::Vector2i getBoardSize() const { return {m_row,m_col}; }
	sf::VideoMode getWindowSize();
	sf::Vector2i getCellIndex(const sf::Vector2f& pos);
	void drawGrid(sf::RenderWindow&);
	int getcol()const { return m_colnum; }
	int getLastcol()const { return m_lastCol; }
private:
	ifstream m_level;
	int m_row, m_col, m_amountBombs;
	int m_colnum;
	int m_lastCol;
};

