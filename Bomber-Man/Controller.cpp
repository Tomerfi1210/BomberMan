#include "Controller.h"
#include "Bomb.h"
#include "GiftFactory.h"

Controller::Controller() : m_board(new Board())
{
}
//--------------------------------------------------------------------
void Controller::run(sf::RenderWindow &m_window)
{

	if (!m_board->readFile(m_guards, m_staticBoard, m_robot, 0))
		m_window.close();
	m_window.create(m_board->getWindowSize(), 32u, sf::Style::Close);
	printBoard(m_window);
	m_window.display();
	m_score = m_guards.size() * 20;

	sf::Event event{};
	while (m_window.isOpen())
	{
		if (m_robot->getLife() == 0)
			m_window.close();

		m_window.clear();//clear the window.

		handleEvents(m_window,event);//mostly to set bombs on board.

		m_robot->setDirection(event);//robot direction movement.

		collides(m_window);// check collision

		if (!isStop)
			movePlayers();

		eraseBombs();//erase bombs that needs to explode.

  		checkExploded(m_window); //checking if any bomb need to be explode.


		printBoard(m_window);//print all objects on the map.

		m_window.display();//display all the objeccts on map.

	}//TODO make a move and check for collision. maybe hold an integer to know if the move is ok and than update.
	//TODO orginaize the controller.
}

//----------------------------------------------------------------------

Controller::~Controller()
{
}
//----------------------------------------------------------------------
void Controller::eraseBombs()
{
	for (size_t i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs[i]->timeToClean())
			m_bombs.erase(m_bombs.begin() + i);
	}
}
//-----------------------------------------------------------------------
void Controller::handleEvents(sf::RenderWindow &m_window, sf::Event &event)
{
	if (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			case sf::Keyboard::Space:
				setBomb();
				break;
			}
			break;
		}
	}
}
//------------------------------------------------------------
void Controller::collides(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_staticBoard.size(); i++)
	{

		if (m_robot->collideHandler(*m_staticBoard[i]))
		{
			if (typeid(*m_staticBoard[i]) == typeid(Door))
			{
				newLevel(window);
				return;
			}
		}
	}

	for (auto& enemy : m_guards)
	{
		if (enemy->collideHandler(*m_robot))
		{
			resetLevel(window);
			break;
		}
	}

	for (auto &bomb : m_bombs)
	{
		if (bomb->collideHandler(*m_robot) && bomb->fireIsCreate())
		{
			static int time = 0;
			if(time >= 30)
			resetLevel(window);

			time++;
			if (time >= 31)
				time = 0;
			break;
		}
	}

	for (size_t i = 0 ; i < m_guards.size() ; i++)
	{
		for (size_t j = 0; j < m_bombs.size(); j++)
		{
			if (m_guards[i]->collideHandler(*m_bombs[j]) && m_bombs[j]->fireIsCreate())
			{
				m_robot->increasScore();
				m_guards.erase(m_guards.begin() + i);
				break;
			}
		}	
	}

	for (size_t j = 0; j < m_guards.size(); j++)
	{
		for (size_t i = 0; i < m_staticBoard.size(); i++)
		{
			if(m_guards[j]->collideHandler(*m_staticBoard[i]))
			break;
		}
	}
	
	for (size_t i = 0; i < m_staticBoard.size(); i++)
	{
		for (size_t j = 0; j < m_bombs.size(); j++)
		{
			if (m_staticBoard[i]->collideHandler(*m_bombs[j]) && m_bombs[j]->fireIsCreate())
			{
				static int time = 0;//every 3 times rand a gift.
				if (time == 1)
				{
					//trying to get pointer of gift object
					auto pos = m_staticBoard[i]->getPosition();
					auto position = getPosOn(pos);

					auto ptr = GiftFactory::create(position);
					if (ptr != nullptr)
						m_gifts.push_back(std::move(ptr));
				}
				m_staticBoard.erase(m_staticBoard.begin() + i);//erase rock from the game.

				time++;
				if (time >= 3)
					time = 0;
				break;
			}
		}
	}

	for (size_t i = 0; i < m_gifts.size(); i++)
	{
		if (m_robot->collideHandler(*m_gifts[i])) {
			std::cout << "yes";
			m_gifts.erase(m_gifts.begin() + i);
		}
	}
}
//-----------------------------------------------------------
void Controller::drawBackGround(sf::RenderWindow &m_window)
{
	sf::Sprite b(*Pictures::getInstance().getBack());
	m_window.draw(b);
}
//-----------------------------------------------------------
void Controller::movePlayers()
{
	m_robot->move(*m_board);
	for (auto& temp : m_guards)
		temp->move(*m_board);
}
//----------------------------------------------------------------
void Controller::printBoard(sf::RenderWindow &window)
{
	drawBackGround(window);
	//m_board->drawGrid(window);
	drawSide(window);
	for (const auto &guards : m_guards)
		guards->draw(window);
	for (const auto &stat : m_staticBoard)
		stat->draw(window);
	m_robot->draw(window);
	for (const auto &bomb : m_bombs)
		bomb->draw(window);
	for (const auto& gift : m_gifts)
		gift->draw(window);
}
//------------------------------------------------------------
void Controller::setBomb()
{
	sf::Vector2f pos;
	pos = m_robot->getPosition();
	
	auto cell = m_board->getCellIndex(pos); //because when we set the bomb it should be here.
	pos.x = PIC_SIZE * cell.x;
	pos.y = PIC_SIZE * cell.y;
	
	//to not put a bomb on top of another
	for (size_t i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs.at(i)->getPosition() == (m_robot->getPosition()))
		{
			return;
		}
	}
 	std::unique_ptr<Bomb> bomb(std::make_unique<Bomb>(pos));
	m_robot->bombCounterDown();
	m_bombs.push_back(std::move(bomb));
}
//------------------------------------------------------------------------
void Controller::checkExploded(sf::RenderWindow & window)
{
	for (int i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs[i]->exploded())//התפוצצה וגם האש לא נוצרה
			return ;
	}
}
//-------------------------------------------------------------------------
sf::Vector2f Controller::getPosOn(sf::Vector2f &pos)
{
	auto cell = m_board->getCellIndex(pos);
	pos.x = PIC_SIZE * cell.x;
	pos.y = PIC_SIZE * cell.y;
	sf::Vector2f newPos = { pos.x,pos.y };
	return newPos;
}
//------------------------------------------------------------------------------
void Controller::stopGift()
{
}
void Controller::handleText(sf::RenderWindow & m_window, const sf::String & name, const sf::Vector2f & pos)
{
	sf::Text t;
	t.setFont(*Pictures::getInstance().getFont());
	t.setString(name);
	t.setFillColor(sf::Color::Green);
	t.setPosition(pos);
	t.setCharacterSize(20);
	t.setOutlineColor(sf::Color::Red);
	m_window.draw(t);
}
void Controller::handleValues(sf::RenderWindow & m_window, const int & value, const sf::Vector2f & pos)
{
	sf::Text n;
	n.setFont(*Pictures::getInstance().getFont());
	n.setString(std::to_string(value));
	n.setFillColor(sf::Color::Red);
	n.setPosition(pos);
	n.setCharacterSize(20);
	n.setOutlineColor(sf::Color::Red);
	m_window.draw(n);
}
//------------------------------------------------------------------------------------
void Controller::newLevel(sf::RenderWindow &m_window) //loading the next level once you meet the door.
{
	std::cout << "new level";
	//m_robot.setScore(m_score);
	m_bombs.clear();
	m_guards.clear();
	m_staticBoard.clear();
	m_gifts.clear();
	m_robot->resetPos();

	m_robot->setScore(m_score);
	if (m_board->readFile(m_guards, m_staticBoard, m_robot, m_board->getcol()))
	{
		m_currLvl++;
		if (m_currLvl == LEVELS-1) {
			sf::Sprite sp;
			exit(EXIT_SUCCESS);
			
		}
	}
		//print_win(m_window); //TODO, call in screen //win sceen
	//m_board->printBoard(m_bombs, m_guards, m_staticBoard, m_robot, m_window);
	m_window.create(m_board->getWindowSize(), 32u, sf::Style::Close);
}
//---------------------------------------------------------------------
void Controller::resetLevel(sf::RenderWindow & m_window)
{
	std::cout << "reset level";
	m_bombs.clear();
	m_gifts.clear();
	for (auto& guard : m_guards)
		guard->resetPos();

	m_robot->resetPos();
}
void Controller::drawSide(sf::RenderWindow & m_window)
{
	handleText(m_window, "Life", { 910, 120 });
	handleText(m_window, "Bombs", { 910, 170 });
	handleText(m_window, "Score", { 910, 220 });
	handleValues(m_window, m_robot->getLife(), { 1050, 120 });
	handleValues(m_window, m_robot->getCountBombs(), { 1050, 170 });
	handleValues(m_window, m_robot->getScore(), { 1050, 220 });

	//-----------------------

	sf::Texture *t1;
	t1 = (Pictures::getInstance().getTexture(Restart_b));
	sf::Sprite s1;
	s1.setTexture(*t1);
	s1.setPosition(1030, 25);
	m_window.draw(s1);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		sf::FloatRect bounds = s1.getGlobalBounds();
		if (bounds.contains(mouse))
		{
			resetLevel(m_window);
		}
	}

	//-----------------------------------------

	sf::Texture *t2;
	t2 = (Pictures::getInstance().getTexture(Pause_b));
	sf::Sprite s2;
	s2.setTexture(*t2);
	s2.setPosition(970, 25);
	m_window.draw(s2);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		sf::FloatRect bounds = s2.getGlobalBounds();
		if (bounds.contains(mouse))
		{
			isStop = true;
		}
	}
	//-------------------------------------

	sf::Texture *t3;
	t3 = (Pictures::getInstance().getTexture(Play_b));
	sf::Sprite s3;
	s3.setTexture(*t3);
	s3.setPosition(910, 25);
	m_window.draw(s3);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		sf::FloatRect bounds = s3.getGlobalBounds();
		if (bounds.contains(mouse))
		{
			isStop = false;
		}
	}

	//sf::Texture *t4;
	//t4.loadFromFile("Images/baby.png");
	//sf::Sprite s4;
	//s4.setTexture(t4);
	//s4.setPosition(880, 400);
	//m_window.draw(s4);
}
//------------------------------------------------------------------------
