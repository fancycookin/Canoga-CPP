#include "Tournment.h"
#include <iostream>



Tournment::Tournment()
{
	m_rounds = 1;
	m_computer = Computer();
	m_human = Human();
}


Tournment::~Tournment()
{
}

int Tournment::GetRounds()
{
	return m_rounds;
}

void Tournment::Handicap(Game &newGame) {
	if (newGame.getWinner()->getPlayerType() == "Human" && newGame.getFirstPlayer()->getPlayerType() == "Human") {
		m_computer.setAdvantage();
	}
	else if (newGame.getWinner()->getPlayerType() == "Computer" && newGame.getFirstPlayer()->getPlayerType() == "Computer") {
		m_human.setAdvantage();
	}
	else if (newGame.getWinner()->getPlayerType() == "Human" && newGame.getFirstPlayer()->getPlayerType() == "Computer") {
		m_human.setAdvantage();
	}
	else if (newGame.getWinner()->getPlayerType() == "Computer" && newGame.getFirstPlayer()->getPlayerType() == "Human") {
		m_computer.setAdvantage();
	}
}

bool Tournment::startGame() {
	string input;
	Game newGame = Game(m_human, m_computer);
	cout << "Would you like to play a game?" << endl;
	cout << "Enter 'play' or 'quit': ";
	input = newGame.getInputFromUser(m_human, "start");
	do {
		if (input == "start") {
			if (system("CLS")) system("clear");
			newGame.playGame(m_rounds);
			m_rounds++;
			cout << "Would you like to play round #" << m_rounds << " ?" << endl;
			input = newGame.getInputFromUser(m_human, "start");
			m_human.clearFlags();
			m_computer.clearFlags();
		}
		else {
			cout << "Rounds played: " << m_rounds << endl;
			newGame.getBoardViewObject()->displayScore();
			cout << "Quitting the game..." << endl;
			return false;
		}
	} while (input != "quit");
}