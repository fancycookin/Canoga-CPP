#pragma once
#include <map>
class Player;
using namespace std;
class Board
{
public:
	Board();
	Board(int a_numberOfRows);
	~Board();
	bool isCovered(Player& a_player, int a_square);
	int getMaxRows();
	map<int,bool>* getHumanRows();
	map<int, bool>* getComputerRows();

private:
	map<int, bool> m_humanRows;
	map<int, bool> m_computerRows;
	int m_maxRows;
	int initializeRows(int a_numberOfRows);



};

