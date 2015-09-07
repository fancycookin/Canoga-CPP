#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	Human();
	using Player::Player;
	~Human();
private:
	bool verifyInput(string a_selection);
};

