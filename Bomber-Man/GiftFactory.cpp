#include "GiftFactory.h"



GiftFactory::GiftFactory()
{
}


GiftFactory::~GiftFactory()
{
}

std::unique_ptr<Gifts> GiftFactory::create(sf::Vector2f &place)
{
	static int gift = 0;
	char tmp;
	switch (gift)
	{
	case 0:
		tmp = Lighting_c;
		break;
	case 1:
		tmp = Speed_c;
		break;
	case 2:
		tmp = Bomb_Gift_c;
		break;
	default:
		break;
	}
	gift++;
	if (gift >= 3)
		gift = 0;
	auto it = getMap().find(tmp); //looking for cell in map
	if (it == getMap().end()) //if cell does not exist
		return nullptr;
	return it->second(place); //call the function that creates the pointer
}

bool GiftFactory::registerit(const char & name, std::unique_ptr<Gifts>(*f)(sf::Vector2f &))
{
	getMap().emplace(name, f); //insert into map
	return true;
}

myGiftsMap & GiftFactory::getMap()
{
	static myGiftsMap m_map;
	return m_map;
}
