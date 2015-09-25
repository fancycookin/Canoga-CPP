#include "Tournment.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <regex>



Tournment::Tournment()
{
	m_rounds = 1;
	m_computer = Computer();
	m_human = Human();
}


Tournment::~Tournment()
{
}

int Tournment::getRounds()
{
	return m_rounds;
}

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

void Tournment::displayLoadFileName() {
	cout << "What is the name of the file you would like to load." << endl;
	cout << "Enter \"EXIT\" to exit." << endl;
}

/* *********************************************************************
Function Name: LoadGame
Purpose: Load game from a specific state.
Parameters: none
Return Value: boolean true or false
Local Variables: line as a string,
input as a string,
myFile as ifstream,
findTile regex,
myIterator regex_iterator,
endIterator regex_iterator,
tmp as Tile,
tmp as string,
myScore as int,
myWins as int,
findScoreOrWins regex,
findHumanOrCPU regex
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
			regex findSquare("([1-9]|[*]|-)");
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
			m_human.setGameRule(humanRow.capacity());

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
			m_game.setGameRule(humanRow.capacity());
			m_game.setLoadedRound(computerRow, humanRow);

			return true;
		}
		else {
			cout << "Unable to open file, try again." << endl;
			return false;
		}
}

bool Tournment::startGame() {
	string input;
	m_game = Game(m_human, m_computer);
	cout << "Would you like to play a game?" << endl;
	cout << "Enter 'play', 'load' or 'quit': ";
	input = m_game.getInputFromUser(m_human, "start");
	do {
		if (input == "load") {
			//Game m_game = Game(m_human, m_computer);
			if (loadGame()) {
				//m_game.setIsLoaded(true);
				if (!m_game.playGame(m_rounds)) {
					input = "quit";
					continue;
				}
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
			if (!m_game.playGame(m_rounds)) {
				input = "quit";
				continue;
			}
			handicap(m_game);
			m_rounds++;
			cout << "Would you like to play round #" << m_rounds << " ?" << endl;
			input = m_game.getInputFromUser(m_human, "start");
			m_human.clearFlags();
			m_computer.clearFlags();
		}
		else if(input == "quit" || input == "saved") {
			if (m_game.isGameStarted()) {
				cout << "Rounds played: " << m_rounds << endl;
				m_game.getBoardViewObject()->displayScore();
				displayWinner();
			}
			cout << "Quitting the game..." << endl;
			return false;
		}
	} while (input != "quit");
}