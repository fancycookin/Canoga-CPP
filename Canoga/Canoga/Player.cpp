#include "Player.h"
#include <typeinfo>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <stdlib.h>

Player::Player()
{
	setPlayerType("Player");
	m_score = 0;
	m_roundScore = 0;
	m_advantagePoints = 0;
	m_wins = 0;
	m_isOneDieMode = false;
	m_isTurn = false;
	m_isWon = false;
	m_wentFirst = false;
	m_wonByCover = false;
	m_wonByUncover = false;
	
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

int Player::getAdvantage() {
	return m_advantagePoints;
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

void Player::setRoundScore(int a_score)
{
	m_roundScore = a_score;
}

int Player::getRoundScore()
{
	return m_roundScore;
}

Board* Player::getBoard()
{
	return m_playerBoard;
}

bool Player::setOneDieMode(bool a_flag)
{
	m_isOneDieMode = a_flag;
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

bool Player::addScore(int a_score)
{
	m_score += a_score;
	return true;
}

bool Player::setTurn()
{
	m_isTurn = !m_isTurn;
	return true;
}

void Player::setTurn(bool a_flag)
{
	m_isTurn = a_flag;
}

void Player::setIsWon()
{
	m_isWon = true;
}

bool Player::getWentFirst()
{
	return m_wentFirst;
}

void Player::setWentFirst(bool a_bool)
{
	m_wentFirst = a_bool;
}

bool Player::isWon()
{
	if (m_isWon) return true;
	else return false;
}

void Player::clearFlags()
{
	m_isOneDieMode = false;
	m_isTurn = false;
	m_isWon = false;
	m_wonByCover = false;
	m_wonByUncover = false;
	m_roundScore = 0;
}

void Player::setCoverSquare(int a_square)
{
	//if (isUncoverable(a_player,a_square)) return false;
	//else {
	if (a_square != 0) {
		if (m_playerType == "Human") {
			map<int, bool> *ptr = m_playerBoard->getHumanRows();
			//m_playerBoard.getMap()[a_square] = true;
			ptr->at(a_square) = true;

		}
		else {
			map<int, bool> *ptr = m_playerBoard->getComputerRows();
			//m_playerBoard.getMap()[a_square] = true;
			ptr->at(a_square) = true;
		}
	}
	//}
}

void Player::setUncoverSquare(int a_square)
{
	//if (isCoverable(a_player, a_square)) return false;
	//else {
	if (a_square != 0) {
		if (m_playerType == "Human") {
			map<int, bool> *ptr = m_playerBoard->getHumanRows();
			ptr->at(a_square) = false;
		}
		else {
			map<int, bool> *ptr = m_playerBoard->getComputerRows();
			ptr->at(a_square) = false;
		}
	}
	//}
}

void Player::setWonByCover()
{
	m_wonByCover = true;
}

void Player::setWonByUncover()
{
	m_wonByUncover = true;
}

string Player::getWonBy()
{
	if (m_wonByCover) {
		return "cover";
	}
	if (m_wonByUncover) {
		return "uncover";
	}
}

 void Player::setAdvantage(int a_roundScore)
{
	int advantageSum = a_roundScore;
	int sum = 0;
	do
	{
		int digit1 = advantageSum % 10;
		advantageSum /= 10;
		int digit2 = advantageSum % 10;
		advantageSum /= 10;

		int sum = digit1 + digit2;
		advantageSum = sum;

		//print digit
	} while (advantageSum > 9);

	m_advantagePoints = advantageSum;
}

 void Player::loadDiceFile()
 {
	 string line;
	 ifstream myFile("dice.txt");
	 if (myFile.is_open()) {

		 while (getline(myFile, line)) {
			 regex findDiceRoll("\\d+");
			 {
				 regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findDiceRoll);
				 regex_iterator<string::iterator> endIterator;
				 //Add all the values from the file to the board
				 int sum = 0;
				 while (myIterator != endIterator) {
					 sum += stoi(myIterator->str());
					 myIterator++;
				 }
				 m_diceRolls.push(sum);
			 }
		 }
	 }

 }



