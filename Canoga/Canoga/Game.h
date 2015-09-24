#pragma once
#include "Human.h"
#include "Computer.h"
#include "BoardView.h"
#include "Board.h"
class Game
{
public:
	Game(Human& a_human, Computer& a_computer);
	~Game();
	int getGameRule();
	string getInputFromUser(Human &a_user, string a_inputType);
	void playGame(int a_roundNumber);
	Human *m_human;
	Computer *m_computer;
	Player *m_firstPlayer;
	bool setGameRule(string a_gameRule);
	int m_gameRule;
	bool isWon();
	void setWon(Player& a_player);
	bool isFirstPlay();
	void setIsFirstPlay();


	void setNewRound();
	void askGameRule();
	Player* getWinner();
	Player* getFirstPlayer();
	Board* getBoardObjet();
	BoardView* getBoardViewObject();

	bool playRound();
	int rollDice(Player& a_player);
	int rollDie(Player& a_player);
	//bool playTurn();
	void setFirstPlayer();

	int m_playerDiceSum, m_computerDiceSum;
	Computer::Moves m_computerMoves;
private:
	bool m_isWonGame;
	bool m_firstPlay;
	BoardView m_boardView;
	Board m_board;



};

