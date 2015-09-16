#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	Human();
	Human(Board &a_board);
	//using Player::Player;
	~Human();
	bool verifyInput(string a_input, string a_inputType);
private:
	/*
	bool verifyGameRule(string a_selection);
	bool verifyRollDice(string a_selection);
	bool verifyRollChoice(string a_selection);
	bool verifyCoverSquare(string a_selection);
	bool verifyUncoverSquare(string a_selection);
	bool verifyFileName(string a_selection);
	*/

};

