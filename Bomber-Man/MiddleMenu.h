#pragma once
#include "Menu.h"
class MiddleMenu : public Menu
{
public:
	MiddleMenu();
	virtual void getOptionFromUser(sf::RenderWindow&);
	~MiddleMenu();
};

