/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#include "Player.h"
#include <typeinfo>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <stdlib.h>

/* *********************************************************************
Function Name: Player
Purpose: Default Constructor for Player
Parameters: none
Return Value: none
Local Variables: none
Algorithm: set player type, reset score, round score, advantage points
			number of wins and all win flags.
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: Player
Purpose: destructor for player
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Player::~Player()
{
}

/* *********************************************************************
Function Name: getPlayerType
Purpose: return type of player
Parameters: none
Return Value: type of player as a string
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
string Player::getPlayerType()
{
	return m_playerType;
}

/* *********************************************************************
Function Name: setPlayerType
Purpose: set the player type field for the player Human or Computer
Parameters: string to be set as player type
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setPlayerType(string a_playerType)
{
	if(a_playerType == "Human" || a_playerType == "Computer") 
		m_playerType = a_playerType;
}

/* *********************************************************************
Function Name: getWins
Purpose: return number of wins
Parameters: none
Return Value: return number of wins
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
int Player::getWins()
{
	return m_wins;
}

/* *********************************************************************
Function Name: getScore
Purpose: return total score of all rounds
Parameters: none
Return Value: total score of all rounds
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
int Player::getScore()
{
	return m_score;
}

/* *********************************************************************
Function Name: getAdvantage
Purpose: return number of advantage square
Parameters: none
Return Value: int - advantage square
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
int Player::getAdvantage() {
	return m_advantagePoints;
}

/* *********************************************************************
Function Name: setConnectedBoard
Purpose: connect a player to a board
Parameters: reference to the board to be the end connection
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setConnectedBoard(Board& a_board)
{
	m_playerBoard = &a_board;
}

/* *********************************************************************
Function Name: isOneDieMode
Purpose: check if player the flag that holds flag if player can roll one die
Parameters: none
Return Value: true if player can roll one die, else false
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::isOneDieMode()
{
	if (m_isOneDieMode) return true;
	else return false;
}

/* *********************************************************************
Function Name: isTurn
Purpose: check if the flag for if it is the player's turn
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::isTurn()
{
	if (m_isTurn) return true;
	else return false;
}

/* *********************************************************************
Function Name: isCoverable
Purpose: check if a certain square is coverable by a certain player
Parameters: Player a_player - player that is requesting the check
			int a_square - square requested to be checked
Return Value: true if is it coverable, false if it is not coverable
Local Variables: none
Algorithm: check if a square is covered, if is it, return false as the square
			is not coverable,
			else the square is coverable so return true
Assistance Received: none
********************************************************************* */
bool Player::isCoverable(Player a_player, int a_square)
{
	if (m_playerBoard->isCovered(a_player,a_square)) return false;
	else return true;
}

/* *********************************************************************
Function Name: isUncoverable
Purpose: check if a certain square is uncoverable by a certain player
Parameters: Player a_player - player that is requesting the check
			int a_square - square resquested to be checked
Return Value:  true if it is uncoverable, false if it is not uncoverable
Local Variables: none
Algorithm: check if a square is covered, if is it, return true as the square
			is uncovercoverable,
			else the square is not covered so return false it is uncoverable
Assistance Received: none
********************************************************************* */
bool Player::isUncoverable(Player a_player, int a_square)
{
	if (m_playerBoard->isCovered(a_player, a_square)) return true;
	return false;
}

/* *********************************************************************
Function Name: setRoundScore
Purpose: change the total round score to a sepcific number
Parameters: int a_score - the new total round score number
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setRoundScore(int a_score)
{
	m_roundScore = a_score;
}

/* *********************************************************************
Function Name: getRoundScore
Purpose: return the total round score
Parameters: none
Return Value: int - the total round score of a player
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
int Player::getRoundScore()
{
	return m_roundScore;
}

/* *********************************************************************
Function Name: getBoard
Purpose: get the player's connected board object
Parameters: none
Return Value: return's a Board pointer to the player's connected board
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Board* Player::getBoard()
{
	return m_playerBoard;
}

/* *********************************************************************
Function Name: setOneDieMode
Purpose: turn the one die flag on or off
Parameters: bool a_flag - true or false for on or off
Return Value: return true on success
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::setOneDieMode(bool a_flag)
{
	m_isOneDieMode = a_flag;
	return true;
}

/* *********************************************************************
Function Name: setWin
Purpose: set the number of wins for a player
Parameters: new number of wins
Return Value: bool - return true on success
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::setWin(int a_wins)
{
	m_wins = a_wins;
	return true;
}

/* *********************************************************************
Function Name: addWin
Purpose: increments the number of wins
Parameters: none
Return Value: bool - returns true if successful
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::addWin()
{
	m_wins++;
	return true;
}

/* *********************************************************************
Function Name: setScore
Purpose: sets a new given score for the player
Parameters: int a_score - new score
Return Value: true when successful
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::setScore(int a_score)
{
	m_score = a_score;
	return true;
}

/* *********************************************************************
Function Name: addScore
Purpose: add a given number of points to the player's score
Parameters: int a_score - new score
Return Value: true when successful
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::addScore(int a_score)
{
	m_score += a_score;
	return true;
}

/* *********************************************************************
Function Name: setTurn
Purpose: toggle the player's turn flag
Parameters: none
Return Value: true when successful
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::setTurn()
{
	m_isTurn = !m_isTurn;
	return true;
}

/* *********************************************************************
Function Name: setTurn
Purpose: OVerloaded setTurn() - set the player's trun flag
Parameters: bool a_flag - new bool
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setTurn(bool a_flag)
{
	m_isTurn = a_flag;
}

/* *********************************************************************
Function Name: setIsWon
Purpose: set a player to win
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setIsWon()
{
	m_isWon = true;
}

/* *********************************************************************
Function Name: getWentFirst
Purpose: check if a player went first
Parameters: none
Return Value: bool - return if player went first
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::getWentFirst()
{
	return m_wentFirst;
}

/* *********************************************************************
Function Name: setWentFirst
Purpose: set that a player went first
Parameters: bool a_bool - flag
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setWentFirst(bool a_bool)
{
	m_wentFirst = a_bool;
}

/* *********************************************************************
Function Name: isWon
Purpose: check if player has won
Parameters: none
Return Value: bool - if player has won, return true, else return false
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::isWon()
{
	if (m_isWon) return true;
	else return false;
}

/* *********************************************************************
Function Name: clearFlags
Purpose: clear the win, turn, one die mode, round score, and win type flags
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::clearFlags()
{
	m_isOneDieMode = false;
	m_isTurn = false;
	m_isWon = false;
	m_wonByCover = false;
	m_wonByUncover = false;
	m_roundScore = 0;
}

/* *********************************************************************
Function Name: setCoverSquare
Purpose: cover a square selected by player
Parameters: int a_square - the square selected
Return Value: none
Local Variables: *ptr - pointer to the players row in the board
Algorithm: get the selected square, cover it
Assistance Received: none
********************************************************************* */
void Player::setCoverSquare(int a_square)
{
	if (a_square != 0) {
		if (m_playerType == "Human") {
			map<int, bool> *ptr = m_playerBoard->getHumanRows();
			ptr->at(a_square) = true;
		}
		else {
			map<int, bool> *ptr = m_playerBoard->getComputerRows();
			ptr->at(a_square) = true;
		}
	}
}

/* *********************************************************************
Function Name: setUncoverSquare
Purpose: uncover a square selected by player
Parameters: int a_square - the square selected
Return Value: none
Local Variables: *ptr - pointer to the players row in the board
Algorithm: get the selected square, uncover it
Assistance Received: none
********************************************************************* */
void Player::setUncoverSquare(int a_square)
{
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
}

/* *********************************************************************
Function Name: setWonByCover
Purpose: set a win that a player has won by covering all own squares
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setWonByCover()
{
	m_wonByCover = true;
}

/* *********************************************************************
Function Name: setWonByUncover
Purpose: set a win that a player has b uncover all opponents squares
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Player::setWonByUncover()
{
	m_wonByUncover = true;
}

/* *********************************************************************
Function Name: getWonBy
Purpose: return the way a player won
Parameters: none
Return Value: "cover" if player won by covering, "uncover" if player won
			 by uncovering
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
string Player::getWonBy()
{
	if (m_wonByCover) {
		return "cover";
	}
	if (m_wonByUncover) {
		return "uncover";
	}
}

/* *********************************************************************
Function Name: setAdvantage
Purpose: calculate the advantage points when a player wins
Parameters: int a_roundScore - the sum of points of the won round
Return Value: none
Local Variables: int advantageSum - variable to hold the round's score
				 int sum - temp sum of the advantage
				 int digit1 - first digit of the round score number
				 int digit2 - second digit of the round score number

Algorithm: get first digit, get second digit, get the sum, then keep doing 
			that until the sum is less than 9
Assistance Received: none
********************************************************************* */
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

 /* *********************************************************************
 Function Name: loadDiceFile
 Purpose: load the file in which the dice rolls are saved
 Parameters: none
 Return Value: none
 Local Variables: string line - line read from file
					ifstream myfile - the dice file
 Algorithm: read line by line each dice roll, if its two numbers on a line,
			add them and store that as a dice roll
 Assistance Received: none
 ********************************************************************* */
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



