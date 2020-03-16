#include "SmartGuard.h"
#include "Board.h"
#include "Bomb.h"
#include "Keys.h"
#include "Fire.h"
#include "DynamicFactory.h"

SmartGuard::SmartGuard(sf::Vector2f &guardpos) : Guards(SmartGuard_type,guardpos) 
{
	m_dirr = Down_d;
}

void SmartGuard::move(const Board & board)
{
	if (m_timeSGuard.getElapsedTime().asSeconds() >= m_moveTimeS.asSeconds())
	{
		if (Collide)
		{
			if (m_timeSGuard.getElapsedTime().asSeconds() >= m_randTime.asSeconds()) {
				m_dir = (Direction_t)(rand() % Max_D);
			}
			SetDirctionGuard();
			Collide = false;
			m_sprite.move(m_step);//TODO check if move is valid in the screen.
		}
		else
			moveManhathen(board);

		m_stepCount++;
		m_timeSGuard.restart();
	}
	if (m_stepCount >= 3)
		m_stepCount = 0;

	sf::IntRect tmp(PLAYER_WIDTH * m_stepCount, m_dir * PLAYER_WIDTH, PLAYER_WIDTH, PLAYER_WIDTH);
	m_sprite.setTextureRect(tmp);
}

void SmartGuard::moveManhathen(const Board &board)
{
	double minDistance =  board.getBoardSize().x * board.getBoardSize().y * 3; 
	sf::Vector2f minPosition = m_sprite.getPosition();
	sf::Vector2f CopyminPosition = m_sprite.getPosition();

	checkPosition(m_robot->getPosition(), { (float)m_sprite.getPosition().x + m_speed , (float)m_sprite.getPosition().y }, minDistance, minPosition, board);
	checkPosition(m_robot->getPosition(), { (float)m_sprite.getPosition().x - m_speed, (float)m_sprite.getPosition().y }, minDistance, minPosition, board);
	checkPosition(m_robot->getPosition(), { (float)m_sprite.getPosition().x, (float)m_sprite.getPosition().y - m_speed }, minDistance, minPosition, board);
	checkPosition(m_robot->getPosition(), { (float)m_sprite.getPosition().x, (float)m_sprite.getPosition().y + m_speed }, minDistance, minPosition, board);

	m_dir = SetDirection(CopyminPosition, minPosition);

	auto next = minPosition;
	next.x -= m_sprite.getPosition().x;
	next.y -= m_sprite.getPosition().y;

	m_sprite.move(next);	
}

double SmartGuard::distance(const sf::Vector2f & v1, const sf::Vector2f & v2)
{
	return std::sqrt(std::pow(abs(v1.x - v2.x), 2)
		+ std::pow(abs(v1.y - v2.y), 2));
}

void SmartGuard::checkPosition(const sf::Vector2f &robotPosition, const sf::Vector2f &nextPosition,
	double &minDistance, sf::Vector2f &minPosition, const Board &board)
{//TODO adding if its available move function
//if (!board.staticCrash(nextPosition, WALL) && !board.staticCrash(nextPosition, ROCK))
	if (distance(robotPosition, nextPosition) < minDistance)
	{
		minDistance = distance(robotPosition, nextPosition);
		minPosition = nextPosition;
	}

}

Direction_t SmartGuard::SetDirection(const sf::Vector2f &old, const sf::Vector2f &newPos)
{
	if (old.y > newPos.y)
		return Left;//for up
	if (old.y < newPos.y)
		return Right;//for down
	if (old.x < newPos.x)
		return Up;//for right
	if (old.x > newPos.x)
		return Down;//for left
}
SmartGuard::~SmartGuard()
{
}

bool SmartGuard::isCollide(const sf::FloatRect & rect) const
{
	sf::FloatRect temp = { rect.left - 1, rect.top - 2, rect.width - 2, rect.height - 2 };
	//in order to check the next move
	sf::FloatRect newRec = { m_sprite.getGlobalBounds().left + m_step.x - 1,
							m_sprite.getGlobalBounds().top + m_step.y,
							m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height };
	if (newRec.intersects(temp))
	{
		return true;

	}
	return false;
}

bool SmartGuard::collideHandler(GameObjects & other)
{
	return other.collideHandler(*this);
}

bool SmartGuard::collideHandler(Robot & other)
{
	return other.collideHandler(*this);
}

bool SmartGuard::collideHandler(Rock & other)
{
	m_step = { 0,0 };
	Collide = true;
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool SmartGuard::collideHandler(Wall & other)
{
	m_step = { 0,0 };
	Collide = true;
	return other.isCollide(m_sprite.getGlobalBounds());
}

bool SmartGuard::collideHandler(Fire & other)
{
	if (other.isCollide(m_sprite.getGlobalBounds())) {
		std::cout << "SmartGuard Vs Fire" << std::endl;
		return true;
	}
	return false;
}

bool SmartGuard::collideHandler(Bomb & other)
{
	return other.collideHandler(*this);
}




bool SmartGuard::m_registered = DynamicFactory::registerit(Smart_Guard_c, [](sf::Vector2f &pos) -> std::unique_ptr<Guards> { return std::make_unique< SmartGuard>( pos ); });