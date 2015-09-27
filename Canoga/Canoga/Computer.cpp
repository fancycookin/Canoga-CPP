/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#include "Computer.h"
#include <iostream>

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
	m_goRollOneDice = false;
	m_moveFree = false;


}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
Computer::~Computer()
{
}


/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
int Computer::getSuggestedMove()
{
	return 0;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
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
	int* m_coverSelections = new int [a_gameRule];
	int* m_uncoverSelections = new int [a_gameRule];
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
	for (int i = 0; i < a_gameRule;i++) {
		if (m_coverSelections[i] == a_diceSum) {
			m_moveFree = true;
			m_moves.m_isCoverMove = true;
			m_coverMoveSet1.clear();
			m_coverMoveSet1.push_back(m_coverSelections[i]);
		}
		for (int j = i + 1; j < 12; j++) {
			if (m_coverSelections[j] + m_coverSelections[i] == a_diceSum) {
				m_moveFree = true;
				m_moves.m_isCoverMove = true;
				m_coverMoveSet2.clear();
				m_coverMoveSet2.push_back(m_coverSelections[j]);
				m_coverMoveSet2.push_back(m_coverSelections[i]);
			}
			for (int k = j + 1; k < 12; k++) {
				if (m_coverSelections[k] + m_coverSelections[j] + m_coverSelections[i] == a_diceSum) {
					m_moveFree = true;
					m_moves.m_isCoverMove = true;
					m_coverMoveSet3.clear();
					m_coverMoveSet3.push_back(m_coverSelections[k]);
					m_coverMoveSet3.push_back(m_coverSelections[j]);
					m_coverMoveSet3.push_back(m_coverSelections[i]);
				}
				for (int q = k + 1; q < 12; q++) {
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
