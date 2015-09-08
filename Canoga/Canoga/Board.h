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
	int getMaxRows();
	map<int,bool>* getMap();

private:
	map<int, bool> m_squareRows;
	int m_maxRows;
	int initializeRows(int a_numberOfRows);



};

