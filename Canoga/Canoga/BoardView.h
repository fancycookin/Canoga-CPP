#pragma once
#include "Board.h"
#include "Player.h"
class BoardView
{
public:
	BoardView(Player &a_player,Player &a_player2);
	~BoardView();
	void refreshDisplay();
	void display();
	void displayScore();

private:
	Player *m_player;
	Player *m_player2;
};

