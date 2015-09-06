#pragma once
#include <map>
using namespace std;
class Board
{
public:
	Board();
	Board(int a_numberOfRows);
	~Board();
	bool isCovered(int a_square);
	map<int,bool> getMap();

private:
	int initializeRows(int a_numberOfRows);
	map<int, bool> m_squareRows;
	int m_maxRows;


};

