#include "Computer.h"



Computer::Computer()
{
}


Computer::Computer(Board &a_board, int a_gameRule) : Player(a_board, a_gameRule)
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
