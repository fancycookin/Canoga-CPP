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
	int getMaxSquares();
	bool setMaxSquares(int a_maxSquares);
	map<int,bool>* getHumanRows();
	map<int, bool>* getComputerRows();

private:
	map<int, bool> m_humanRow;
	map<int, bool> m_computerRow;
	int m_maxSquares;
	int initializeRows(int a_numberOfSquares);



};

