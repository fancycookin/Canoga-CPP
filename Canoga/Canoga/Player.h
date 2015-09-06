#pragma once
class Player
{
public:
	Player();
	~Player();
	int GetNumberOfWins();
	int GetScore();
	bool isTurn();
private:
	int m_score, m_wins;
	bool m_isTurn;
	bool SetWin();
	bool AddWin();
	bool SetScore();
	bool AddScore();
	bool SetTurn();


};

