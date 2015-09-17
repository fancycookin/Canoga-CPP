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

Board::Board() {


}

Board::Board(int a_numberOfRows)
{
	m_maxSquares = 0;
	initializeRows(a_numberOfRows);

}


Board::~Board()
{
}

bool Board::isCovered(Player& a_player, int a_square)
{

	cout << typeid(a_player).name() << endl;
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

int Board::getMaxSquares()
{
	return m_maxSquares;
}

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

map<int,bool>*Board::getHumanRows()
{
	return &m_humanRow;
}

map<int, bool>*Board::getComputerRows()
{
	return &m_computerRow;
}



int Board::initializeRows(int a_numberOfRows) {
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


