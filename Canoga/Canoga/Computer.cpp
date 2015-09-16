#include "Computer.h"



Computer::Computer()
{
}


Computer::Computer(Board &a_board) : Player(a_board)
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
