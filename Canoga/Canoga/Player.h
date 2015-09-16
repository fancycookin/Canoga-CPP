#pragma once
#include "Board.h"
//class Board;
class Player
{
public:
	Player();
	Player(Board& a_board,int a_gameRule);
	~Player();
	string getPlayerType();
	void setPlayerType(string a_playerType);
	int getWins();
	int getScore();
	bool isOneDieMode();
	bool isTurn();
	bool isCoverable(Player a_player, int a_square);
	bool isUncoverable(Player a_player, int a_square);
	bool setCoverSquare(Player a_player, int a_square);

	bool setUncoverSquare(Player a_player, int a_square);



	Board* getBoard();


	bool setOneDieMode();
	bool setWin(int a_wins);
	bool addWin();
	bool setScore(int a_score);
	bool addScore();
	bool setTurn();


private:
	Board *m_playerBoard;
	int m_score, m_wins;
	bool m_isTurn, m_isOneDieMode;
	string m_playerType;



};

