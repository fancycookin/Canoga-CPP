#include "Computer.h"


Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
}

Computer::~Computer()
{
}

int Computer::getSuggestedMove()
{
	return 0;
}

int Computer::searchAndDestroy()
{
	return 0;
}
