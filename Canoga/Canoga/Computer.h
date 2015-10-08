/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#pragma once
#include "Player.h"
#include <vector>
class Computer :
	public Player
{
public:
	Computer();
	//using Player::Player;
	~Computer();
	
	struct Moves {
		vector<int> m_coverMoveSet = vector<int>();
		vector<int> m_uncoverMoveSet = vector<int>();
		bool m_isCoverMove = false;
		bool m_isUncoverMove = false;
	};
	Moves setBestMove(Player& a_aidPlayer, Player& a_enemyPlayer, int a_gameRule, int a_diceSum, bool a_isFirstPlay);
private:
	//flags

	//bool m_goComputerHigherSquares;
	//bool m_goComputerLowerSquares;
	bool m_goRollOneDice;
	//bool m_goHumanHigherSquares;
	//bool m_goHumanLowerSquares;
	bool m_moveFree;


	// okay here's the plan
	/* go for 7 to n squares first
	* if not available
	* go for 1 to 6 squares next
	* if not available
	* uncover opponents 7 to n squares first
	* if not available
	* uncover opponents 1 to 6 squares next
	* special condition: if play is almost about to win by covering his own squares, try to sobatage
	*/

};

