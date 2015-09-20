#include "Computer.h"

Computer::Computer() : Player()
{
	Player::setPlayerType("Computer");
	m_goComputerHigherSquares = false;
	m_goComputerLowerSquares = false;
	m_goRollOneDice = false;
	m_goHumanHigherSquares = false;
	m_goHumanLowerSquares = false;

}

Computer::~Computer()
{
}

int Computer::getSuggestedMove()
{
	return 0;
}

void Computer::setBestMove(int a_gameRule, int a_diceSum)
{
	int m_selections[5] = { 0,0,0,0,0 };
	for (int i = 7; i < a_gameRule + 1;i++) {
		if (this->isCoverable(*this, i)) {
			m_selections[i -7] = i;
			// then target the top 7 to n squares
			// why? will this will enable you to 
			// control the game by the option to throw only one dice
		}
	}

	//so this madness right here
	// will determine if we can actually make a move with the dice sum that we have
	// madness
	for (int i = 0; i < a_gameRule - 4; i++) {
		if (m_selections[i] == a_diceSum) {
			m_goComputerHigherSquares = true;
			break;
		}
		for (int j = i + 1; j < a_gameRule -3; j++) {
			if (m_selections[i] + m_selections[j] == a_diceSum) {
				m_goComputerHigherSquares = true;
				break;
			}
			for (int k = j + 1; k < a_gameRule - 2;k++) {
				if (m_selections[i] + m_selections[j] + m_selections[k] == a_diceSum) {
					m_goComputerHigherSquares = true;
					break;
				}
				for (int q = k + 1;q < a_gameRule -1;q++) {
					if (m_selections[i] + m_selections[j] + m_selections[k] + m_selections[q] == a_diceSum) {
						m_goComputerHigherSquares = true;
						break;
					}
					for (int t = q + 1; t < a_gameRule; t++) {
						if (m_selections[i] + m_selections[j] + m_selections[k] + m_selections[q] + m_selections[t] == a_diceSum) {
							m_goComputerHigherSquares = true;
							break;
						}
					}
				}
			}
		}
	}

	// end madness


}
