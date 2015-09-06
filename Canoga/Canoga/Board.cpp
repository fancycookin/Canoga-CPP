//*********************************************************
//* Name: Ihab Hamid                                      *
//* Project: Project 1 C++ Canoga                         *
//* Class: CMPS 366 Organization of Programming Languages *
//* Date: 9/25/15                                         *
//*********************************************************



#include "Board.h"
#include "Game.h"



Board::Board(int a_numberOfRows)
{
	InitializeRows(a_numberOfRows);

}


Board::~Board()
{
}

int Board::InitializeRows(int a_numberOfRows) {
	if (a_numberOfRows < 9 || a_numberOfRows > 12) {

		return 1;
	}

	for (int i = 0; i < m_maxRows; i++) {
		m_humanRows.insert(pair<int, bool>(i + 1, false));
		m_computerRows.insert(pair<int, bool>(i + 1, false));
	}
	return 0;
}

