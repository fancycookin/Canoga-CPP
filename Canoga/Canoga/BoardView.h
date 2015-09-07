#pragma once
#include "Board.h"
#include "Player.h"
class BoardView
{
public:
	BoardView(Player &a_player);
	~BoardView();
	void RefreshDisplay();
	void Display();

private:
	Player *m_player;
};

