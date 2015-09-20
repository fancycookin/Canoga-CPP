#pragma once
#include "Player.h"
class Computer :
	public Player
{
public:
	Computer();
	//using Player::Player;
	~Computer();
	int getSuggestedMove();
	void setBestMove(int a_gameRule, int a_diceSum);
private:
	//flags
	bool m_goComputerHigherSquares;
	bool m_goComputerLowerSquares;
	bool m_goRollOneDice;
	bool m_goHumanHigherSquares;
	bool m_goHumanLowerSquares;


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

