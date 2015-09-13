#pragma once
#include "Human.h"
#include "Computer.h"
class Game
{
public:
	Game();
	~Game();
	int getGameRule();

private:
	Human m_human;
	Computer m_computer;
	int m_gameRule;
	bool setGameRule(int a_gameRule);
	void setNewRound();
	//void askGameRule();
	string getInputFromUser(Human &user, string inputType);
	void playRound();
	void askMove();
	int rollDice();
	int rollDie();
	//bool playTurn();
	void setFirstPlayer();
	int m_playerDiceSum,m_computerDiceSum;
	Player m_firstPlayer;
};

