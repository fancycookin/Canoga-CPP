#include "Computer.h"
#include <iostream>

Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
	//m_goComputerHigherSquares = false;
	//m_goComputerLowerSquares = false;
	m_goRollOneDice = false;
	//m_goHumanHigherSquares = false;
	//m_goHumanLowerSquares = false;
	m_moveFree = false;
	//m_computerRowMove = false;
	//m_humanRowMove = false;


}

Computer::~Computer()
{
}


int Computer::getSuggestedMove()
{
	return 0;
}

Computer::Moves Computer::setBestMove(Player& a_aidPlayer, Player& a_enemyPlayer, int a_gameRule, int a_diceSum, bool a_isFirstPlay)
{
	// see if we can cover top
	//the first two were indexed at 5 but now its 6 cuz why not

	//implement this:

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
	//int m_compHighSelections[6] = { 0,0,0,0,0,0 };
	//int m_humanHighSelections[6] = { 0,0,0,0,0,0 };
	//int m_compLowSelections[6] = { 0,0,0,0,0,0 };
	//int m_humanLowSelections[6] = { 0,0,0,0,0,0 };

	//int computerRowCounter = 0;
	//int humanRowCounter = 0;

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

	/*
	for (int i = 7; i < a_gameRule + 1;i++) {
		if (this->isCoverable(*this, i)) {
			m_compHighSelections[computerRowCounter] = i;
			computerRowCounter++;
			// then target the top 7 to n squares
			// why? will this will enable you to 
			// control the game by the option to throw only one dice
		}
		if (a_human.isUncoverable(a_human, i)) {
			m_humanHighSelections[humanRowCounter] = i;
			humanRowCounter++;
		}
	}

	
	//get lower part coverable and uncoverable squares
	computerRowCounter = 0;
	humanRowCounter = 0;
	for (int i = 1; i < 7;i++) {
		if (this->isCoverable(*this, i)) {
			m_compLowSelections[computerRowCounter] = i;
			computerRowCounter++;
		}
		if (a_human.isUncoverable(a_human, i)) {
			m_humanHighSelections[humanRowCounter] = i;
			humanRowCounter++;
		}
	}
	*/
	

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
		//cout << "No Move available to be made by computer. Ending turn..." << endl;
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
	

	
	/*


	if (m_moveFree && m_moves.m_isCoverMove) {
		//cout << "Computer decided to cover own squares." << endl;
		if (!m_coverMoveSet4.empty()) { 
			m_moves.m_coverMoveSet = m_coverMoveSet4;
			return m_moves;
		}
		else if (!m_coverMoveSet3.empty()) { 
			m_moves.m_coverMoveSet = m_coverMoveSet3;
			return m_moves;
		}
		else if (!m_coverMoveSet2.empty()) {
			m_moves.m_coverMoveSet = m_coverMoveSet2; 
			return m_moves;
		}
		else if (!m_coverMoveSet1.empty()) {
			m_moves.m_coverMoveSet = m_coverMoveSet1;
			return m_moves;
		}
	}
	if (m_moveFree && m_moves.m_isUncoverMove) {
		//cout << "Computer decided to uncover your squares." << endl;
		if (!m_uncoverMoveSet4.empty()) { 
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet4;
			return m_moves;
		}
		else if (!m_uncoverMoveSet3.empty()) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet3;
			return m_moves;
		}
		else if (!m_uncoverMoveSet2.empty()) {
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet2;
			return m_moves;
		}
		else if (!m_uncoverMoveSet1.empty()) { 
			m_moves.m_uncoverMoveSet = m_uncoverMoveSet1;
			return m_moves;
		}
	}

	*/

	//so this madness right here
	// will determine if we can actually make a move with the dice sum that we have
	// madness

	//todo: add lower bracket flag validations
	/*
	for (int i = 0; i < 1; i++) {
		if (m_compHighSelections[i] == a_diceSum) {
			m_goComputerHigherSquares = true;
		}
		if (m_humanHighSelections[i] == a_diceSum) {
			m_goHumanHigherSquares = true;
		}
		for (int j = i + 1; j < 2; j++) {
			if (m_compHighSelections[i] + m_compHighSelections[j] == a_diceSum) {
				m_goComputerHigherSquares = true;
			}
			if (m_humanHighSelections[i] + m_humanHighSelections[j] == a_diceSum) {
				m_goHumanHigherSquares = true;
			}
			for (int k = j + 1; k < 3;k++) {
				if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] == a_diceSum) {
					m_goComputerHigherSquares = true;
				}
				if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] == a_diceSum) {
					m_goHumanHigherSquares = true;
				}
				for (int q = k + 1;q < 4;q++) {
					if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] == a_diceSum) {
						m_goComputerHigherSquares = true;
					}
					if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] == a_diceSum) {
						m_goHumanHigherSquares = true;
					}
					for (int t = q + 1; t < 5; t++) {
						if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] + m_compHighSelections[t] == a_diceSum) {
							m_goComputerHigherSquares = true;
						}
						if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] + m_humanHighSelections[t] == a_diceSum) {
							m_goHumanHigherSquares = true;
						}
						for (int h = t + 1;h < 6;h++) {
							if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] + m_compHighSelections[t] + m_compHighSelections[h] == a_diceSum) {
								m_goComputerHigherSquares = true;
							}
							if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] + m_humanHighSelections[t] + m_humanHighSelections[h] == a_diceSum) {
								m_goHumanHigherSquares = true;
							}
						}
					}
				}
			}
		}
	}
	*/
	// end madness
	/*
	for (int i = 0; i < 7;i++) {
		if (m_compHighSelections[i] == a_diceSum) {
			m_goComputerHigherSquares = true;
		}
		if (m_compLowSelections[i] == a_diceSum) {
			m_goComputerLowerSquares = true;
		}
		for (int j = i + 1; j < 7 -2; j++) {
			if (m_compHighSelections[j] + m_compHighSelections[i] == a_diceSum) {
				m_goComputerHigherSquares = true;
			}
			if (m_compLowSelections[j] + m_compLowSelections[i]  == a_diceSum) {
				m_goComputerLowerSquares = true;
			}
			for (int k = j + 1; k < 7 - 3; k++) {
				if (m_compHighSelections[k] + m_compHighSelections[j] + m_compHighSelections[i]  == a_diceSum) {
					m_goComputerHigherSquares = true;
				}
				if (m_compLowSelections[k] + m_compLowSelections[j] + m_compLowSelections[i] == a_diceSum) {
					m_goComputerLowerSquares = true;
				}
				for (int q = k + 1; q < 7 -4; q++) {
					if (m_compHighSelections[q] + m_compHighSelections[k] + m_compHighSelections[j] + m_compHighSelections[i] == a_diceSum) {
						m_goComputerHigherSquares = true;
					}
					if (m_compLowSelections[q] + m_compLowSelections[k] + m_compLowSelections[j] + m_compLowSelections[i] == a_diceSum) {
						m_goComputerLowerSquares = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < 1; i++) {
		if (m_compHighSelections[i] == a_diceSum) {
			m_goComputerHigherSquares = true;
		}
		if (m_humanHighSelections[i] == a_diceSum) {
			m_goHumanHigherSquares = true;
		}
		for (int j = i + 1; j < 2; j++) {
			if (m_compHighSelections[i] + m_compHighSelections[j] == a_diceSum) {
				m_goComputerHigherSquares = true;
			}
			if (m_humanHighSelections[i] + m_humanHighSelections[j] == a_diceSum) {
				m_goHumanHigherSquares = true;
			}
			for (int k = j + 1; k < 3;k++) {
				if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] == a_diceSum) {
					m_goComputerHigherSquares = true;
				}
				if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] == a_diceSum) {
					m_goHumanHigherSquares = true;
				}
				for (int q = k + 1;q < 4;q++) {
					if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] == a_diceSum) {
						m_goComputerHigherSquares = true;
					}
					if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] == a_diceSum) {
						m_goHumanHigherSquares = true;
					}
					for (int t = q + 1; t < 5; t++) {
						if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] + m_compHighSelections[t] == a_diceSum) {
							m_goComputerHigherSquares = true;
						}
						if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] + m_humanHighSelections[t] == a_diceSum) {
							m_goHumanHigherSquares = true;
						}
						for (int h = t + 1;h < 6;h++) {
							if (m_compHighSelections[i] + m_compHighSelections[j] + m_compHighSelections[k] + m_compHighSelections[q] + m_compHighSelections[t] + m_compHighSelections[h] == a_diceSum) {
								m_goComputerHigherSquares = true;
							}
							if (m_humanHighSelections[i] + m_humanHighSelections[j] + m_humanHighSelections[k] + m_humanHighSelections[q] + m_humanHighSelections[t] + m_humanHighSelections[h] == a_diceSum) {
								m_goHumanHigherSquares = true;
							}
						}
					}
				}
			}
		}
	}

	*/
}
