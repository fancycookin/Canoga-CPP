#include "Player.h"
#include <typeinfo>


Player::Player()
{
	setPlayerType("Player");
	m_score = 0;
	m_wins = 0;
	m_isOneDieMode = false;
	m_isTurn = false;
	
}


Player::~Player()
{
}

string Player::getPlayerType()
{
	return m_playerType;
}

void Player::setPlayerType(string a_playerType)
{
	m_playerType = a_playerType;
}

int Player::getWins()
{
	return m_wins;
}

int Player::getScore()
{
	return m_score;
}

void Player::setConnectedBoard(Board& a_board)
{
	m_playerBoard = &a_board;
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

bool Player::isCoverable(Player a_player, int a_square)
{
	if (m_playerBoard->isCovered(a_player,a_square)) return false;
	else return true;
}

bool Player::isUncoverable(Player a_player, int a_square)
{
	if (m_playerBoard->isCovered(a_player, a_square)) return true;
	return false;
}

Board* Player::getBoard()
{
	return m_playerBoard;
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

bool Player::isWon()
{
	if (m_isWon) return true;
	else return false;
}

bool Player::setCoverSquare(Player a_player,int a_square)
{
	if (isUncoverable(a_player,a_square)) return false;
	else {
		if (m_playerType == "Human") {
			map<int, bool> *ptr = m_playerBoard->getHumanRows();
			//m_playerBoard.getMap()[a_square] = true;
			ptr->at(a_square) = true;
			int x;
			x = 5;

		}
		else {
			map<int, bool> *ptr = m_playerBoard->getComputerRows();
			//m_playerBoard.getMap()[a_square] = true;
			ptr->at(a_square) = true;
		}
		return true;
	}
}

bool Player::setUncoverSquare(Player a_player, int a_square)
{
	if (isCoverable(a_player, a_square)) return false;
	else {
		if (m_playerType == "Human") {
			map<int, bool> *ptr = m_playerBoard->getHumanRows();
			ptr->at(a_square) = false;
		}
		else {
			map<int, bool> *ptr = m_playerBoard->getComputerRows();
			ptr->at(a_square) = false;
		}
		return true;
	}
}



