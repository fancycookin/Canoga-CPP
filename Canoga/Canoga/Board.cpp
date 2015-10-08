//*********************************************************
//* Name: Ihab Hamid                                      *
//* Project: Project 1 C++ Canoga                         *
//* Class: CMPS 366 Organization of Programming Languages *
//* Date: 9/25/15                                         *
//*********************************************************
#include "Board.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include "Player.h"

/* *********************************************************************
Function Name: Board	
Purpose: default constructor for Board
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Board::Board() {


}

/* *********************************************************************
Function Name: Board
Purpose: overloaded constructor for Board class
Parameters: int a_numberOfRows - maximum number of squares on a row
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Board::Board(int a_numberOfRows)
{
	m_maxSquares = 0;
	initializeRows(a_numberOfRows);

}


/* *********************************************************************
Function Name: Board
Purpose: default destructor for Board class
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Board::~Board()
{
}

/* *********************************************************************
Function Name: isCovered
Purpose: check if a square on a specified player's row is covered
Parameters: Player& a_player - player's row
			int a_square - square to be checked
Return Value: bool if covered return true, if not return false
Local Variables: none
Algorithm: check the square in the specified row
Assistance Received: none
********************************************************************* */
bool Board::isCovered(Player& a_player, int a_square)
{

	if (a_player.getPlayerType() == "Human") {
		if (m_humanRow[a_square]) return true;
		else return false;
	}
	if (a_player.getPlayerType() == "Computer") {
		if (m_computerRow[a_square]) return true;
		else return false;
	}
	else {
		throw exception("Object is neither computer or player");
		return false;
	}
}



/* *********************************************************************
Function Name: setMaxSquares
Purpose: set max number of squares on a row
Parameters: int a_maxRows - max number of squares
Return Value: true if number of max squares is valid, false if not
Local Variables:
Algorithm: check if passed max number of squares is between 9 and 11
Assistance Received: none
********************************************************************* */
bool Board::setMaxSquares(int a_maxRows)
{
	if (a_maxRows < 9 || a_maxRows > 12) {
		return false;
	}
	else {
		m_maxSquares = a_maxRows;
		return true;
	}
}

/* *********************************************************************
Function Name: getHumanRows
Purpose: returns a pointer to the human players rows
Parameters: none
Return Value: points to the uman players row map
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
map<int,bool>*Board::getHumanRows()
{
	return &m_humanRow;
}

/* *********************************************************************
Function Name: getComputerRows
Purpose: returns a poiner to the computer players rows
Parameters: none
Return Value: a pointer to the computer players row map
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
map<int, bool>*Board::getComputerRows()
{
	return &m_computerRow;
}
/* *********************************************************************
Function Name: initializeRows
Purpose: fill both human and computer rows
Parameters: int a_numberOfRows - maximum number of squares
Return Value: return true if sucessfully filled rows, false if number of rows is out of range
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Board::initializeRows(int a_numberOfRows) {
	if (setMaxSquares(a_numberOfRows)) {
		for (int i = 0; i < m_maxSquares; i++) {
			m_humanRow.insert(pair<int, bool>(i + 1, false));
			m_computerRow.insert(pair<int, bool>(i + 1, false));
		}
		return true;
	}
	else {
		cerr << "Number of Maximum Squares must be between 9 and 11";
		return false;
	}
}


