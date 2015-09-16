#pragma once
#include "Human.h"
#include "Computer.h"
class Game
{
public:
	Game(int a_gameRule);
	~Game();
	int getGameRule();
	//string getInputFromUser(Human &a_user, string a_inputType);
	Board m_board;
	Human m_human;
	Computer m_computer;
	Player m_firstPlayer;

private:

	int m_gameRule;
	bool setGameRule(int a_gameRule);
	void setNewRound();
	//void askGameRule();

	void playRound();
	void askMove();
	int rollDice();
	int rollDie();
	//bool playTurn();
	void setFirstPlayer();
	int m_playerDiceSum,m_computerDiceSum;

};

