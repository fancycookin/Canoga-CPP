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
	bool verifyGameRule(string a_selection);
	bool verifyCommand(string a_selection);
	bool verifyRollChoice(string a_selection);
};

