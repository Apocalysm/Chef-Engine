#include "Time.h"

#include <SFML\System.hpp>

using ce::Time;

Time::Time()
{
	time = new sf::Time();
}


Time::~Time()
{
}


float ce::Time::AsSeconds() const
{
	return time->asSeconds();
}


unsigned int ce::Time::AsMilliseconds() const
{
	return time->asMilliseconds();
}
