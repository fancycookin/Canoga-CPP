#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	Human();
	~Human();
private:
	bool verifyInput(string a_selection);
};

