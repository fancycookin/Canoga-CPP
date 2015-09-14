#include "Computer.h"



Computer::Computer()
{
}


Computer::Computer(int a_gameRule) : Player(a_gameRule)
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
