#include "Computer.h"
#include <iostream>

Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
	m_goComputerHigherSquares = false;
	m_goComputerLowerSquares = false;
	m_goRollOneDice = false;
	m_goHumanHigherSquares = false;
	m_goHumanLowerSquares = false;
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

Computer::Moves Computer::setBestMove(Human& a_human,int a_gameRule, int a_diceSum)
{
	// see if we can cover top
	//the first two were indexed at 5 but now its 6 cuz why not
	Moves m_moves;
	vector<int> m_finalComputerSet4 = vector<int>();
	vector<int> m_finalComputerSet3 = vector<int>();
	vector<int> m_finalComputerSet2 = vector<int>();
	vector<int> m_finalComputerSet1 = vector<int>();

	vector<int> m_finalHumanSet4 = vector<int>();
	vector<int> m_finalHumanSet3 = vector<int>();
	vector<int> m_finalHumanSet2 = vector<int>();
	vector<int> m_finalHumanSet1 = vector<int>();
	int m_selectionsComputer[11] = { 0 };
	int m_selectionsHuman[11] = { 0 };
	int m_selectionsComputerCounter = 0;
	int m_selectionsHumanCounter = 0;
	int m_compHighSelections[6] = { 0,0,0,0,0,0 };
	int m_humanHighSelections[6] = { 0,0,0,0,0,0 };
	int m_compLowSelections[6] = { 0,0,0,0,0,0 };
	int m_humanLowSelections[6] = { 0,0,0,0,0,0 };

	int computerRowCounter = 0;
	int humanRowCounter = 0;

	for (int i = 0; i < a_gameRule; i++) {
		if (this->isCoverable(*this, i + 1)) {
			m_selectionsComputer[i] = i+1;
			m_selectionsComputerCounter++;
		}
		if (a_human.isUncoverable(a_human, i + 1)) {
			m_selectionsHuman[i] = i + 1;
			m_selectionsHumanCounter++;
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
		if (m_selectionsComputer[i] == a_diceSum) {
			m_moveFree = true;
			m_moves.m_computerRowMove = true;
			m_finalComputerSet1.clear();
			m_finalComputerSet1.push_back(m_selectionsComputer[i]);
		}
		for (int j = i + 1; j < 12; j++) {
			if (m_selectionsComputer[j] + m_selectionsComputer[i] == a_diceSum) {
				m_moveFree = true;
				m_moves.m_computerRowMove = true;
				m_finalComputerSet2.clear();
				m_finalComputerSet2.push_back(m_selectionsComputer[j]);
				m_finalComputerSet2.push_back(m_selectionsComputer[i]);
			}
			for (int k = j + 1; k < 12; k++) {
				if (m_selectionsComputer[k] + m_selectionsComputer[j] + m_selectionsComputer[i] == a_diceSum) {
					m_moveFree = true;
					m_moves.m_computerRowMove = true;
					m_finalComputerSet4.clear();
					m_finalComputerSet3.push_back(m_selectionsComputer[k]);
					m_finalComputerSet3.push_back(m_selectionsComputer[j]);
					m_finalComputerSet3.push_back(m_selectionsComputer[i]);
				}
				for (int q = k + 1; q < 12; q++) {
					if (m_selectionsComputer[q] + m_selectionsComputer[k] + m_selectionsComputer[j] + m_selectionsComputer[i] == a_diceSum) {
						m_moveFree = true;
						m_moves.m_computerRowMove = true;
						m_finalComputerSet4.clear();
						m_finalComputerSet4.push_back(m_selectionsComputer[q]);
						m_finalComputerSet4.push_back(m_selectionsComputer[k]);
						m_finalComputerSet4.push_back(m_selectionsComputer[j]);
						m_finalComputerSet4.push_back(m_selectionsComputer[i]);
					}
				}
			}
		}
	}

	for (int i = 0; i < a_gameRule;i++) {
		if (m_selectionsHuman[i] == a_diceSum) {
			m_moveFree = true;
			m_moves.m_humanRowMove = true;
			m_finalHumanSet1.clear();
			m_finalHumanSet1.push_back(m_selectionsHuman[i]);
		}
		for (int j = i + 1; j < 12; j++) {
			if (m_selectionsHuman[j] + m_selectionsHuman[i] == a_diceSum) {
				m_moveFree = true;
				m_moves.m_humanRowMove = true;
				m_finalHumanSet2.clear();
				m_finalHumanSet2.push_back(m_selectionsHuman[j]);
				m_finalHumanSet2.push_back(m_selectionsHuman[i]);
			}
			for (int k = j + 1; k < 12; k++) {
				if (m_selectionsHuman[k] + m_selectionsHuman[j] + m_selectionsHuman[i] == a_diceSum) {
					m_moveFree = true;
					m_moves.m_humanRowMove = true;
					m_finalHumanSet3.clear();
					m_finalHumanSet3.push_back(m_selectionsHuman[k]);
					m_finalHumanSet3.push_back(m_selectionsHuman[j]);
					m_finalHumanSet3.push_back(m_selectionsHuman[i]);
				}
				for (int q = k + 1; q < 12; q++) {
					if (m_selectionsHuman[q] + m_selectionsHuman[k] + m_selectionsHuman[j] + m_selectionsHuman[i] == a_diceSum) {
						m_moveFree = true;
						m_moves.m_humanRowMove = true;
						m_finalHumanSet4.clear();
						m_finalHumanSet4.push_back(m_selectionsHuman[q]);
						m_finalHumanSet4.push_back(m_selectionsHuman[k]);
						m_finalHumanSet4.push_back(m_selectionsHuman[j]);
						m_finalHumanSet4.push_back(m_selectionsHuman[i]);
					}
				}
			}
		}
	}

	if (!m_moveFree) {
		cout << "No Move available to be made by computer. Ending turn..." << endl;
		return m_moves;
	}
	if (m_moveFree && m_moves.m_computerRowMove) {
		cout << "Computer decided to cover own squares." << endl;
		if (!m_finalComputerSet4.empty()) { 
			m_moves.m_moveSet = m_finalComputerSet4;
			return m_moves;
		}
		else if (!m_finalComputerSet3.empty()) { 
			m_moves.m_moveSet = m_finalComputerSet3;
			return m_moves;
		}
		else if (!m_finalComputerSet2.empty()) {
			m_moves.m_moveSet = m_finalComputerSet2; 
			return m_moves;
		}
		else if (!m_finalComputerSet2.empty()) {
			m_moves.m_moveSet = m_finalComputerSet1;
			return m_moves;
		}
	}
	if (m_moveFree && m_moves.m_humanRowMove) {
		cout << "Computer decided to uncover your squares." << endl;
		if (!m_finalHumanSet4.empty()) { 
			m_moves.m_moveSet = m_finalHumanSet4; 
			return m_moves;
		}
		else if (!m_finalHumanSet3.empty()) {
			m_moves.m_moveSet = m_finalHumanSet3;
			return m_moves;
		}
		else if (!m_finalHumanSet2.empty()) {
			m_moves.m_moveSet = m_finalHumanSet2;
			return m_moves;
		}
		else if (!m_finalHumanSet1.empty()) { 
			m_moves.m_moveSet = m_finalHumanSet1;
			return m_moves;
		}
	}



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
