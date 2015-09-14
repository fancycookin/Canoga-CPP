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
	m_maxRows = 0;
	initializeRows(a_numberOfRows);

}


Board::~Board()
{
}

bool Board::isCovered(Player& a_player, int a_square)
{

	cout << typeid(a_player).name() << endl;
	string temp = a_player.getPlayerType();
	cout << temp;
	//cout << a_player.getPlayerType() << endl;
	if (a_player.getPlayerType() == "Human") {
		if (m_humanRows[a_square]) return true;
		else return false;
	}
	if (a_player.getPlayerType() == "Computer") {
		if (m_computerRows[a_square]) return true;
		else return false;
	}
	else {
		throw exception("Object is neither computer or player");
		return false;
	}
}

int Board::getMaxRows()
{
	return m_maxRows;
}

map<int,bool>*Board::getHumanRows()
{
	return &m_humanRows;
}

map<int, bool>*Board::getComputerRows()
{
	return &m_computerRows;
}

int Board::initializeRows(int a_numberOfRows) {
	if (a_numberOfRows < 9 || a_numberOfRows > 12) {
		return -1;
	}
	m_maxRows = a_numberOfRows;
	for (int i = 0; i < m_maxRows; i++) {
		m_humanRows.insert(pair<int, bool>(i + 1, false));
		m_computerRows.insert(pair<int, bool>(i + 1, false));
	}
	return 0;
}


