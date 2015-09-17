#pragma once
#include "Human.h"
#include "Computer.h"
class Game
{
public:
	Game(Human& a_human, Computer& a_computer);
	~Game();
	int getGameRule();
	//string getInputFromUser(Human &a_user, string a_inputType);
	Board m_board;
	Human *m_human;
	Computer *m_computer;
	Player m_firstPlayer;
	bool setGameRule(string a_gameRule);
	int m_gameRule;

	void setNewRound();
	void askGameRule();
	Player* getWinner();

	void playRound();
	void askMove();
	int rollDice();
	int rollDie();
	//bool playTurn();
	void setFirstPlayer();
	int m_playerDiceSum, m_computerDiceSum;
private:



};

