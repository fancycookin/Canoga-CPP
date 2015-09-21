#pragma once
#include "Player.h"
#include "Human.h"
#include <vector>
class Computer :
	public Player
{
public:
	Computer();
	//using Player::Player;
	~Computer();
	int getSuggestedMove();
	
	struct Moves {
		vector<int> m_moveSet = vector<int>();
		bool m_computerRowMove = false;
		bool m_humanRowMove = false;
	};
	Moves setBestMove(Human& a_human, int a_gameRule, int a_diceSum);
private:
	//flags

	bool m_goComputerHigherSquares;
	bool m_goComputerLowerSquares;
	bool m_goRollOneDice;
	bool m_goHumanHigherSquares;
	bool m_goHumanLowerSquares;
	bool m_moveFree;
	Human *m_human;


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

