#include "Player.h"
#include "Board.h"
#include <ctime>

Player::Player() {

}

Player::Player(int a_gameRule)
{
	m_score = 0;
	m_wins = 0;
	m_isOneDieMode = false;
	m_isTurn = false;
	m_playerBoard =  Board(a_gameRule);
}


Player::~Player()
{
}

int Player::getWins()
{
	return m_wins;
}

int Player::getScore()
{
	return m_score;
}

bool Player::isOneDieMode()
{
	if (m_isOneDieMode) return true;
	else return false;
}

bool Player::isTurn()
{
	if (m_isTurn) return true;
	else return false;
}

bool Player::isCoverable(int a_square)
{
	if (m_playerBoard.isCovered(a_square)) return false;
	else return true;
}

bool Player::isUncoverable(int a_square)
{
	if (m_playerBoard.isCovered(a_square)) return true;
	return false;
}

Board* Player::getBoard()
{
	return &m_playerBoard;
}

bool Player::setOneDieMode()
{
	m_isOneDieMode = !m_isOneDieMode;
	return true;
}

bool Player::setWin(int a_wins)
{
	m_wins = a_wins;
	return true;
}

bool Player::addWin()
{
	m_wins++;
	return true;
}

bool Player::setScore(int a_score)
{
	m_score = a_score;
	return true;
}

bool Player::addScore()
{
	m_score++;
	return true;
}

bool Player::setTurn()
{
	m_isTurn = !m_isTurn;
	return true;
}

bool Player::setCoverSquare(int a_square)
{
	if (isUncoverable(a_square)) return false;
	else {
		map<int,bool> *ptr = m_playerBoard.getMap();
		//m_playerBoard.getMap()[a_square] = true;
		ptr->at(a_square) = true;
		return true;
	}
}

bool Player::setUncoverSquare(int a_square)
{
	if (isCoverable(a_square)) return false;
	else {
		map<int, bool> *ptr = m_playerBoard.getMap();
		ptr->at(a_square) = false;
		return true;
	}
}


int Player::rollDice()
{
	srand(static_cast<unsigned int>(time(0)));
	int value = rand() % 6 + 1;
	value += rand() % 6 + 1;
	return value;
}

int Player::rollDie()
{
	srand(static_cast<unsigned int>(time(0)));
	int value;
	if (!isOneDieMode()) return -1;
	else {
		value = rand() % 6 + 1;
		return value;
	}
}
