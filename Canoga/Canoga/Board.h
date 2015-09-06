#pragma once
#include <map>
using namespace std;
class Board
{
public:
	Board(int a_numberOfRows);
	~Board();
	bool isCovered(int a_square);
	bool isCoverable(int a_square);
	bool isUncoverable(int a_square);
private:
	int InitializeRows(int a_numberOfRows);

	//int m_humanRows[11], m_computerRows[11];
	map<int, bool> m_humanRows, m_computerRows;
	int m_maxRows;
	bool setCoverSquare(int a_square);
	bool setUncoverSquare(int a_square);


};

