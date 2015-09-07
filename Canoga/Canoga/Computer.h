#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	using Player::Player;
	~Computer();
private:
	int getSuggestedMove();
	int searchAndDestroy();
};

