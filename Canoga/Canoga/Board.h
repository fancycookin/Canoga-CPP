/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#pragma once
#include <map>
class Player;
using namespace std;
class Board
{
public:
	Board();
	Board(int a_maxRows);
	~Board();
	bool isCovered(Player& a_player, int a_square);
	bool setMaxSquares(int a_maxSquares);
	map<int,bool>* getHumanRows();
	map<int, bool>* getComputerRows();

private:
	map<int, bool> m_humanRow;
	map<int, bool> m_computerRow;
	int m_maxSquares;
	bool initializeRows(int a_numberOfSquares);



};

