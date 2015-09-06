#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	~Computer();
private:
	int GetSuggestedMove();
	int SearchAndDestroy();
};

