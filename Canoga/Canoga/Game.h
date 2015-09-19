#pragma once
#include "Human.h"
#include "Computer.h"
class Game
{
public:
	Game(Human& a_human, Computer& a_computer);
	~Game();
	int getGameRule();
	string getInputFromUser(Human &a_user, string a_inputType);
	Board m_board;
	Human *m_human;
	Computer *m_computer;
	Player m_firstPlayer;
	bool setGameRule(string a_gameRule);
	int m_gameRule;
	bool isWon();
	void setWon(Player& a_player);

	void setNewRound();
	void askGameRule();
	Player* getWinner();

	void playRound();
	int rollDice(Player& a_player);
	int rollDie(Player& a_player);
	//bool playTurn();
	void setFirstPlayer();
	int m_playerDiceSum, m_computerDiceSum;
private:
	bool m_isWonGame;



};

