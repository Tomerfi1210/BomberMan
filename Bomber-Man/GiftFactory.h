#pragma once
#include "Gifts.h"

typedef std::map<char, std::unique_ptr<Gifts>(*)(sf::Vector2f&)> myGiftsMap;
class GiftFactory
{
public:
	GiftFactory();
	~GiftFactory();
	static std::unique_ptr<Gifts> create(sf::Vector2f&); //gets the key and returns a pointer to new object
	static bool registerit(const char& name, std::unique_ptr<Gifts>(*)(sf::Vector2f&));  //each object will register itself to map 

	//only this class can get map
private:
	static myGiftsMap& getMap();
};

