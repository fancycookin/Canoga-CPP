/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#pragma once
#include "Board.h"
#include <queue>
class Player
{
public:
	Player();
	~Player();
	virtual string getPlayerType();
	virtual string getWonBy();
	virtual void setPlayerType(string a_playerType);
	virtual int getWins();
	virtual int getScore();
	virtual int getRoundScore();
	virtual int getAdvantage();
	virtual bool getWentFirst();
	virtual Board* getBoard();
	
	virtual bool isOneDieMode();
	virtual bool isTurn();
	virtual bool isCoverable(Player a_player, int a_square);
	virtual bool isUncoverable(Player a_player, int a_square);
	virtual bool isWon();

	virtual void setConnectedBoard(Board& a_board);
	virtual bool setOneDieMode(bool a_flag);
	virtual void setRoundScore(int a_score);
	virtual void setCoverSquare(int a_square);
	virtual void setUncoverSquare( int a_square);
	virtual void setWonByCover();
	virtual void setWonByUncover();
	
	virtual void loadDiceFile();
	virtual void setAdvantage(int a_roundScore);
	
	virtual bool setWin(int a_wins);
	virtual bool addWin();
	virtual bool setScore(int a_score);
	virtual bool addScore(int a_score);
	queue<int> m_diceRolls;
	virtual bool setTurn();
	virtual void setTurn(bool a_flag);
	virtual void setIsWon();
	virtual void setWentFirst(bool a_bool);
	virtual void clearFlags();
	

private:
	Board *m_playerBoard;
	int m_score, m_wins;
	int m_roundScore, m_advantagePoints;
	bool m_isTurn, m_isOneDieMode, m_isWon, m_wentFirst;
	bool m_wonByCover, m_wonByUncover;
	string m_playerType;




};

