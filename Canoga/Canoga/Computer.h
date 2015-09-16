#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	//using Player::Player;
	Computer(Board& a_board);
	~Computer();
	int getSuggestedMove();
	int searchAndDestroy();
private:

};

