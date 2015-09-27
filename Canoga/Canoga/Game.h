/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/

#pragma once
#include "Human.h"
#include "Computer.h"
#include "BoardView.h"
#include "Board.h"
class Game
{
public:
	Game();
	Game(Human& a_human, Computer& a_computer);
	~Game();
	Player* getWinner() const;
	Player* getFirstPlayer() const;
	Board* getBoardObjet();
	BoardView* getBoardViewObject();
	int getGameRule() const;
	bool getIsDiceFile() const;
	void setIsDiceFile(bool a_flag);

	bool isWon() const;
	bool isFirstPlay() const;

	bool isGameStarted() const;
	bool isLoaded() const;
	void setFirstPlayer();
	void setIsLoaded(bool a_flag);
	bool setGameRule(string a_gameRule);
	bool setGameRule(int a_gameRule);
	void setWon(Player& a_player);
	void setIsFirstPlay();
	void setLoadedRound(vector<string> a_computerRow, vector<string> a_humanRow);
	void setNewRound();
	void askGameRule();
	void askSaveGame();
	bool playGame(int a_roundNumber);
	bool playRound();
	bool saveGame();
	int rollDice(Player& a_player);
	int rollDie(Player& a_player);
	Computer::Moves m_computerMoves;

	static string getInputFromUser(Human &a_user, string a_inputType);
	Human *m_human;
	Computer *m_computer;
	Player *m_firstPlayer;
private:
	int m_playerDiceSum;
	int m_computerDiceSum;
	int m_gameRule;
	bool m_gameStarted;
	bool m_isWonGame;
	bool m_firstPlay;
	bool m_didHumanMove;
	bool m_didComputerMove;
	bool m_isLoaded;
	bool m_diceFile;
	BoardView m_boardView;
	Board m_board;
};

