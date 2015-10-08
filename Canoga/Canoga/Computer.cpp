/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#include "Computer.h"
#include <iostream>

/* *********************************************************************
Function Name: Computer
Purpose: default constructor for Computer class
Parameters: none
Return Value: none
Local Variables: none
Algorithm: inherits from Player's default constructor
Assistance Received: none
********************************************************************* */
Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
	m_goRollOneDice = false;
	m_moveFree = false;


}

/* *********************************************************************
Function Name: Computer
Purpose: default destructor
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Computer::~Computer()
{
}

/* *********************************************************************
Function Name: setBestMove
Purpose: calculate best move possible
Parameters: Player& a_aidPlayer - player to be aided
			Player& a_enemyPlayer - player to be destroyed
			int a_gameRule - game board size
			int a_diceSum - dice sum
			bool a_isFirstPlay - is it the first round?
Return Value: Moves - a struct of moves and flags
Local Variables: Moves m_moves;
				vector<int> m_coverMoveSet4 - 4 moves cover set of moves
				vector<int> m_coverMoveSet3 - 3 moves cover set of moves
				vector<int> m_coverMoveSet2 - 2 moves cover set of moves
				vector<int> m_coverMoveSet1 - 1 moves cover set of moves

				vector<int> m_uncoverMoveSet4 - 4 moves uncover set of moves
				vector<int> m_uncoverMoveSet3 - 3 moves uncover set of moves
				vector<int> m_uncoverMoveSet2 - 2 moves uncover set of moves
				vector<int> m_uncoverMoveSet1 - 1 moves uncover set of moves
				int* m_coverSelections - array of possible cover selections
				int* m_uncoverSelections - array of possible uncover selections
				int m_coverSelectionsCounter - number of cover selections available
				int m_uncoverSelectionsCounter - number of cover selections available
Algorithm: calculate all possible moves first for player to be aided and save them,
		   calculate all moves makeable moves by the player to be aided using dice sum,
		   calculate if it is better to cover or uncover,
		   return move set with the highest number of moves
		   
Assistance Received: none
********************************************************************* */
Computer::Moves Computer::setBestMove(Player& a_aidPlayer, Player& a_enemyPlayer, int a_gameRule, int a_diceSum, bool a_isFirstPlay)
{
	// see if we can cover top
	//the first two were indexed at 5 but now its 6 cuz why not

	m_moveFree = false;
	Moves m_moves;
	vector<int> m_coverMoveSet4 = vector<int>();
	vector<int> m_coverMoveSet3 = vector<int>();
	vector<int> m_coverMoveSet2 = vector<int>();
	vector<int> m_coverMoveSet1 = vector<int>();

	vector<int> m_uncoverMoveSet4 = vector<int>();
	vector<int> m_uncoverMoveSet3 = vector<int>();
	vector<int> m_uncoverMoveSet2 = vector<int>();
	vector<int> m_uncoverMoveSet1 = vector<int>();
	int m_coverSelections[12] = { 0 };
	int m_uncoverSelections[12] = { 0 };
	int m_coverSelectionsCounter = 0;
	int m_uncoverSelectionsCounter = 0;

	for (int i = 0; i < a_gameRule; i++) {
		if (a_aidPlayer.isCoverable(a_aidPlayer, i + 1)) {
			m_coverSelections[i] = i+1;
			m_coverSelectionsCounter++;
		}
		if (a_enemyPlayer.isUncoverable(a_enemyPlayer, i + 1)) {
			if (a_enemyPlayer.getAdvantage() != i +1 && a_isFirstPlay == false ) {
				m_uncoverSelections[i] = i + 1;
				m_uncoverSelectionsCounter++;
			}
		}
	}

	//pick the one with the highest moves
	//pick computer row first 
	// then if not available go for human's row

	// get al makeable cover moves using dice sum
	for (int i = 0; i < a_gameRule;i++) {
		if (m_coverSelections[i] == a_diceSum) {
			m_moveFree = true;
			m_moves.m_isCoverMove = true;
			m_coverMoveSet1.clear();
			m_coverMoveSet1.push_back(m_coverSelections[i]);
		}
		for (int j = i + 1; j < a_gameRule; j++) {
			if (m_coverSelections[j] + m_coverSelections[i] == a_diceSum) {
				m_moveFree = true;
				m_moves.m_isCoverMove = true;
				m_coverMoveSet2.clear();
				m_coverMoveSet2.push_back(m_coverSelections[j]);
				m_coverMoveSet2.push_back(m_coverSelections[i]);
			}
			for (int k = j + 1; k < a_gameRule; k++) {
				if (m_coverSelections[k] + m_coverSelections[j] + m_coverSelections[i] == a_diceSum) {
					m_moveFree = true;
					m_moves.m_isCoverMove = true;
					m_coverMoveSet3.clear();
					m_coverMoveSet3.push_back(m_coverSelections[k]);
					m_coverMoveSet3.push_back(m_coverSelections[j]);
					m_coverMoveSet3.push_back(m_coverSelections[i]);
				}
				for (int q = k + 1; q < a_gameRule; q++) {
					if (m_coverSelections[q] + m_coverSelections[k] + m_coverSelections[j] + m_coverSelections[i] == a_diceSum) {
						m_moveFree = true;
						m_moves.m_isCoverMove = true;
						m_coverMoveSet4.clear();
						m_coverMoveSet4.push_back(m_coverSelections[q]);
						m_coverMoveSet4.push_back(m_coverSelections[k]);
						m_coverMoveSet4.push_back(m_coverSelections[j]);
						m_coverMoveSet4.push_back(m_coverSelections[i]);
					}
				}
			}
		}
	}

	//get all makeable uncover moves using dice sum
	for (int i = 0; i < a_gameRule;i++) {
		if (m_uncoverSelections[i] == a_diceSum) {
			m_moveFree = true;
			m_moves.m_isUncoverMove = true;
			m_uncoverMoveSet1.clear();
			m_uncoverMoveSet1.push_back(m_uncoverSelections[i]);
		}
		for (int j = i + 1; j < a_gameRule; j++) {
			if (m_uncoverSelections[j] + m_uncoverSelections[i] == a_diceSum) {
				m_moveFree = true;
				m_moves.m_isUncoverMove = true;
				m_uncoverMoveSet2.clear();
				m_uncoverMoveSet2.push_back(m_uncoverSelections[j]);
				m_uncoverMoveSet2.push_back(m_uncoverSelections[i]);
			}
			for (int k = j + 1; k < a_gameRule; k++) {
				if (m_uncoverSelections[k] + m_uncoverSelections[j] + m_uncoverSelections[i] == a_diceSum) {
					m_moveFree = true;
					m_moves.m_isUncoverMove = true;
					m_uncoverMoveSet3.clear();
					m_uncoverMoveSet3.push_back(m_uncoverSelections[k]);
					m_uncoverMoveSet3.push_back(m_uncoverSelections[j]);
					m_uncoverMoveSet3.push_back(m_uncoverSelections[i]);
				}
				for (int q = k + 1; q < a_gameRule; q++) {
					if (m_uncoverSelections[q] + m_uncoverSelections[k] + m_uncoverSelections[j] + m_uncoverSelections[i] == a_diceSum) {
						m_moveFree = true;
						m_moves.m_isUncoverMove = true;
						m_uncoverMoveSet4.clear();
						m_uncoverMoveSet4.push_back(m_uncoverSelections[q]);
						m_uncoverMoveSet4.push_back(m_uncoverSelections[k]);
						m_uncoverMoveSet4.push_back(m_uncoverSelections[j]);
						m_uncoverMoveSet4.push_back(m_uncoverSelections[i]);
					}
				}
			}
		}
	}
	if (!m_moveFree) {
		return m_moves;
	}
	
	//determine which is the best move set and return it
	if (m_moveFree)
	{
		if (!m_coverMoveSet4.empty() && m_moves.m_isCoverMove) {
			m_moves.m_coverMoveSet = m_coverMoveSet4;
			return m_moves;

		}
		if (!m_uncoverMoveSet4.empty() && m_moves.m_isUncoverMove) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet4;
			return m_moves;

		}
		if (!m_coverMoveSet3.empty() && m_moves.m_isCoverMove) {
			m_moves.m_coverMoveSet = m_coverMoveSet3;
			return m_moves;

		}
		if (!m_uncoverMoveSet3.empty() && m_moves.m_isUncoverMove) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet3;
			return m_moves;

		}
		if (!m_coverMoveSet2.empty() && m_moves.m_isCoverMove) {
			m_moves.m_coverMoveSet = m_coverMoveSet2;
			return m_moves;
		}
		if (!m_uncoverMoveSet2.empty() && m_moves.m_isUncoverMove) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet2;
			return m_moves;
		}
		if (!m_coverMoveSet1.empty() && m_moves.m_isCoverMove) {
			m_moves.m_coverMoveSet = m_coverMoveSet1;
			return m_moves;
		}
		if (!m_uncoverMoveSet1.empty() && m_moves.m_isUncoverMove) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet1;
			return m_moves;

		}
	}
}
