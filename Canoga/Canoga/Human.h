/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#pragma once
#include "Player.h"
#include <algorithm>
class Human :
	public Player
{
public:
	Human();
	//using Player::Player;
	~Human();
	bool verifyInput(string a_input, string a_inputType);
	bool is_number(const string& s);
	string toLowerCase(string a_selection);
	void setGameRule(int a_gameRule);
private:
	bool verifyGameRule(string a_selection);
	bool verifyHelp(string a_selection);
	bool verifyRollDice(string a_selection);
	bool verifyOneRoll(string a_selection);
	bool verifyTwoRoll(string a_selection);
	bool verifyRollChoice(string a_selection);
	bool verifyCoverSquare(string a_selection);
	bool verifyUncoverSquare(string a_selection);
	bool verifyFileName(string a_selection);
	bool verifyStartGame(string a_selection);
	bool verifyNumber(string a_selection);
	bool verifyCoverUncoverSquare(string a_selection);
	bool verifySaveGame(string a_selection);
	int m_gameRule;


};

