/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/

#include "Tournment.h"
#include "Player.h"
#include "Computer.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <regex>

/* *********************************************************************
Function Name: Tournment
Purpose: Default constructor for Tournment class
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Tournment::Tournment()
{
	m_rounds = 1;
	m_computer = Computer();
	m_human = Human();
	m_diceFile = true;
}

/* *********************************************************************
Function Name: Tournment
Purpose: Default destructor for Tournment class
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Tournment::~Tournment()
{
}


/* *********************************************************************
Function Name: getRounds
Purpose: To return number of rounds played
Parameters: none
Return Value: number of rounds played: int value
Assistance Received: none
********************************************************************* */
int Tournment::getRounds() const
{
	return m_rounds;
}

/* *********************************************************************
Function Name: isDiceFile
Purpose: To check if dice file to be loaded
Parameters: none
Return Value: true if file to be loaded, false if not: boolean value
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Tournment::isDiceFile() const
{
	return m_diceFile;
}

/* *********************************************************************
Function Name:setDiceFile
Purpose: To set the m_diceFile to true or false
Parameters: bool a_flag - true or false
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Tournment::setDiceFile(bool a_flag)
{
	m_diceFile = a_flag;
}

/* *********************************************************************
Function Name: handicap
Purpose: to calculate the handicap after finishing a round
Parameters: Game &newGame - reference to the round going to be played
Return Value: none
Local Variables: none
Algorithm: 1) check the winner
			2) check who went first
			3) calculate advantage
Assistance Received: none
********************************************************************* */
void Tournment::handicap(Game &newGame) {
	if (newGame.getWinner()->getPlayerType() == "Human" && newGame.getFirstPlayer()->getPlayerType() == "Human") {
		m_computer.setAdvantage(m_human.getRoundScore());
	}
	else if (newGame.getWinner()->getPlayerType() == "Computer" && newGame.getFirstPlayer()->getPlayerType() == "Computer") {
		m_human.setAdvantage(m_computer.getRoundScore());
	}
	else if (newGame.getWinner()->getPlayerType() == "Human" && newGame.getFirstPlayer()->getPlayerType() == "Computer") {
		m_human.setAdvantage(m_human.getRoundScore());
	}
	else if (newGame.getWinner()->getPlayerType() == "Computer" && newGame.getFirstPlayer()->getPlayerType() == "Human") {
		m_computer.setAdvantage(m_computer.getRoundScore());
	}
}

/* *********************************************************************
Function Name: displayWinner
Purpose: display the winner of the tournment
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Tournment::displayWinner() {
	if (m_human.getScore() > m_computer.getScore()) {
		cout << "Winner: Human!" << endl;
	}
	else if (m_computer.getScore() > m_human.getScore()) {
		cout << "Winner: Computer!" << endl;
	}
	else if (m_computer.getScore() == m_human.getScore()) {
		cout << "It's a draw! Noob!" << endl;
	}
}

/* *********************************************************************
Function Name: displayLoadFileName
Purpose: display prompt for the user when load game is requested
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Tournment::displayLoadFileName() {
	cout << "What is the name of the file you would like to load." << endl;
	cout << "Enter \"EXIT\" to exit." << endl;
}

/* *********************************************************************
Function Name: LoadGame
Purpose: Load game from a specific state.
Parameters: none
Return Value: boolean true or false
Local Variables:	string line - read line buffer,
					string firstTurn - holds first turn Player's name
					string nextTurn - holds next turn player's name
					vector<string> computerRow - holds computer's row
					vector<string> humanRow - holds human's row
					int gameRule - holds the board's max sqaure
					int computerScore - computer's score points
					int humanScore - human's score points
					myFile as ifstream,
					findSquare regex,
					myIterator regex_iterator,
					endIterator regex_iterator,
Algorithm: Using regular expressions and the getline function, the function
goes line by line assigning the approriate values to the computer
and human players.  It uses regular expressions to grab the values
from each line.
Assistance Received: none
********************************************************************* */
bool Tournment::loadGame() {
		string line;
		string firstTurn;
		string nextTurn;
		vector<string> computerRow = vector<string>();
		vector<string> humanRow = vector<string>();
		int gameRule = 0;
		int computerScore = 0;
		int humanScore = 0;
		//Ask user for file name
		cout << "Enter name of file you'd like to download: (without .txt extension)" << endl;
		cout << "Enter 'back' to go back." << endl;
		string input = m_game.getInputFromUser(m_human, "filename");
		if (input == "back") {
			return false;
		}
		input = input + ".txt";
		ifstream myFile(input);
		if (myFile.is_open()) {
			
			//Computer
			getline(myFile, line);
			
			//Human Squares
			getline(myFile, line);
			//regex findSquare("([1-9]|[*]|-)");
			regex findSquare("(\\d+|[*]|-)");
			{
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findSquare);
				regex_iterator<string::iterator> endIterator;
				//Add all the values from the file to the board
				while(myIterator != endIterator) {
					computerRow.push_back(myIterator->str());
					myIterator++;
				}
			}
			
			// Computer Score
			regex findScore("\\d+");
			{
				getline(myFile, line);
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findScore);
				regex_iterator<string::iterator> endIterator;
				while (myIterator != endIterator) {
					computerScore = stoi(myIterator->str());
					myIterator++;
				}
			}
			
			//space
			getline(myFile, line);

			//Human
			getline(myFile, line);

			//Human Squares
			getline(myFile, line);
			{
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findSquare);
				regex_iterator<string::iterator> endIterator;
				while (myIterator != endIterator) {
					humanRow.push_back(myIterator->str());
					myIterator++;
				}
			}

			//Human Score
			{
				getline(myFile, line);
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findScore);
				regex_iterator<string::iterator> endIterator;
				while (myIterator != endIterator) {
					humanScore = stoi(myIterator->str());
					myIterator++;
				}
			}

			getline(myFile, line);

			//First Turn
			regex findFirstTurn("Human|Computer");
			{
				getline(myFile, line);
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findFirstTurn);
				regex_iterator<string::iterator> endIterator;
				while (myIterator != endIterator) {
					firstTurn = myIterator->str();
					myIterator++;
				}
			}

			//Next Turn
			regex findNextTurn("Human|Computer");
			{
				getline(myFile, line);
				regex_iterator<string::iterator> myIterator(line.begin(), line.end(), findNextTurn);
				regex_iterator<string::iterator> endIterator;
				while (myIterator != endIterator) {
					nextTurn = myIterator->str();
					myIterator++;
				}
			}
			myFile.close();

			m_computer.setScore(computerScore);
			m_human.setScore(humanScore);
			m_human.setGameRule(humanRow.size());

			if (firstTurn == "Computer") {
				m_computer.setWentFirst(true);
				m_human.setWentFirst(false);
			}
			if (firstTurn == "Human") {
				m_computer.setWentFirst(false);
				m_human.setWentFirst(true);
			}
			if (nextTurn == "Computer") {
				m_computer.setTurn(true);
				m_human.setTurn(false);
			}
			if (nextTurn == "Human") {
				m_computer.setTurn(false);
				m_human.setTurn(true);
			}
			m_game = Game(m_human, m_computer);
			m_game.setIsLoaded(true);
			m_game.setGameRule(humanRow.size());
			m_game.setLoadedRound(computerRow, humanRow);
			if (m_diceFile) {
				m_game.setIsDiceFile(true);
			}
			return true;
		}
		else {
			cout << "Unable to open file, try again." << endl;
			return false;
		}
}

/* *********************************************************************
Function Name: startGame
Purpose: This is the main menu of the game and the gateway to gameplay 
Parameters: none
Return Value: bool - returns true when game quits
Local Variables: string input - user input
Algorithm: 1) give user option to either start a new game, load, or quit
			2) if user picks load - load a previously started game
			3) if user picks play - start a new game 
Assistance Received:
********************************************************************* */
bool Tournment::startGame() {
	string input;
	m_game = Game(m_human, m_computer);

	// if using dice file
	if (m_diceFile) {
		m_human.loadDiceFile();
		m_game.setIsDiceFile(true);
	}
	cout << "Would you like to play a game?" << endl;
	cout << "Enter 'play', 'load' or 'quit': ";
	input = m_game.getInputFromUser(m_human, "start");
	do {
		if (input == "load") {
			//load a previously started game
			if (loadGame()) {
				// if user exits/saves from a play game, then exit from entire game
				if (!m_game.playGame(m_rounds)) {
					input = "quit";
					continue;
				}
				// claculate handicap at end of round
				handicap(m_game);
				m_rounds++;
				cout << "Would you like to play round #" << m_rounds << " ?" << endl;
				input = m_game.getInputFromUser(m_human, "start");
				m_human.clearFlags();
				m_computer.clearFlags();
			}
			else {
				cout << "Would you like to play a game?" << endl;
				cout << "Enter 'play', 'load' or 'quit': ";
				input = m_game.getInputFromUser(m_human, "start");
			}
		}
		if (input == "play") {
			if (system("CLS")) system("clear");
			m_game = Game(m_human, m_computer);
			if (m_diceFile) {
				m_game.setIsDiceFile(true);
			}
			if (!m_game.playGame(m_rounds)) {
				input = "quit";
				continue;
			}
			handicap(m_game);
			m_rounds++;
			cout << "Would you like to play round #" << m_rounds << " ?" << endl;
			input = m_game.getInputFromUser(m_human, "start");
			// reseet players for a new round
			m_human.clearFlags();
			m_computer.clearFlags();
		}
		else if(input == "quit" || input == "saved") {
			if (m_game.isGameStarted()) {
				// game ended, display winner of tournment
				cout << "Rounds played: " << m_rounds << endl;
				m_game.getBoardViewObject()->displayScore();
				displayWinner();
			}
			cout << "Quitting the game..." << endl;
			return true;
		}
	} while (input != "quit");
}