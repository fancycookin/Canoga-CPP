//*********************************************************
//* Name: Ihab Hamid                                      *
//* Project: Project 1 C++ Canoga                         *
//* Class: CMPS 366 Organization of Programming Languages *
//* Date: 9/25/15                                         *
//*********************************************************



#include "Board.h"
#include "Game.h"

Board::Board() {


}

Board::Board(int a_numberOfRows)
{
	initializeRows(a_numberOfRows);

}


Board::~Board()
{
}

bool Board::isCovered(int a_square)
{
	if (m_squareRows[a_square]) return true;
	else return false;
}

map<int,bool> Board::getMap()
{
	return m_squareRows;
}

int Board::initializeRows(int a_numberOfRows) {
	if (a_numberOfRows < 9 || a_numberOfRows > 12) {

		return 1;
	}

	for (int i = 0; i < m_maxRows; i++) {
		m_squareRows.insert(pair<int, bool>(i + 1, false));
	}
	return 0;
}


