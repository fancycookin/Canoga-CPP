#pragma once
#include "Board.h"
//class Board;
class Player
{
public:
	Player();
	~Player();
	string getPlayerType();
	void setPlayerType(string a_playerType);
	int getWins();
	int getScore();
	void setConnectedBoard(Board& a_board);
	bool isOneDieMode();
	bool setOneDieMode(bool a_flag);
	bool isTurn();
	bool isCoverable(Player a_player, int a_square);
	bool isUncoverable(Player a_player, int a_square);
	void setRoundScore(int a_score);
	int getRoundScore();
	void setCoverSquare(int a_square);
	void setUncoverSquare( int a_square);
	void setWonByCover();
	void setWonByUncover();
	string getWonBy();

	void setAdvantage();
	int getAdvantage();



	Board* getBoard();


	bool setWin(int a_wins);
	bool addWin();
	bool setScore(int a_score);
	bool addScore(int a_score);
	bool setTurn();
	void setIsWon();
	bool getWentFirst();
	void setWentFirst(bool a_bool);
	bool isWon();
	void clearFlags();


private:
	Board *m_playerBoard;
	int m_score, m_wins;
	int m_roundScore, m_advantagePoints;
	bool m_isTurn, m_isOneDieMode, m_isWon, m_wentFirst;
	bool m_wonByCover, m_wonByUncover;
	string m_playerType;



};

