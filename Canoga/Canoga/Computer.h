#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	//using Player::Player;
	Computer(Board& a_board, int a_gameRule);
	~Computer();
	int getSuggestedMove();
	int searchAndDestroy();
private:

};

