#include "Game.h"
#include "Player.h"
#include "BoardView.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;


Game::Game(int a_gameRule)
{
	//askGameRule();
	setGameRule(a_gameRule);
	
	setNewRound();
	//m_human = Human(m_gameRule);
	//m_computer = Computer(m_gameRule);
	m_playerDiceSum = 0;
	m_computerDiceSum = 0;
}


Game::~Game()
{
}

int Game::getGameRule()
{
	return m_gameRule;
}

bool Game::setGameRule(int a_gameRule)
{
	if (a_gameRule < 9 || a_gameRule > 11) return false;
	m_gameRule = a_gameRule;
	return true;
}

void Game::setNewRound()
{
	m_board = Board(m_gameRule);
	m_human = Human(m_board,m_gameRule);
	m_computer = Computer(m_board,m_gameRule);
	m_human.setScore(0);
	m_computer.setScore(0);
}
/*
void Game::askGameRule()
{
	string selection;
	cout << "Set the rule of the game.\nHow many squares would you like the game boards to have?" << endl;
	do{
		cout << "Enter a value from 9 - 11: ";
		cin >> selection;
		if (m_human.verifyGameRule(selection)) {
			setGameRule(stoi(selection));
			cout << "Game rule has been set to: " + selection + " squares per board.";
		}
		else {
			cout << "Invalid input.";
		}
	}while(selection.i)
}
*/

void Game::playRound()
{
	if (m_human.isTurn()) {
		askMove();
		  
	}
	else {
		m_computer.searchAndDestroy(); 
	}
}

void Game::askMove()
{
	cout << "What would you like to do bud?";
}

void Game::setFirstPlayer()
{
	while (m_playerDiceSum == m_computerDiceSum) {
		m_playerDiceSum = rollDice();
		m_computerDiceSum = rollDice();
		if (m_playerDiceSum > m_computerDiceSum) {
			m_firstPlayer = m_human;
			m_human.setTurn();
		}
		if (m_computerDiceSum > m_playerDiceSum) {
			m_firstPlayer = m_computer;
			m_computer.setTurn();
		}
	}
}


int Game::rollDice()
{
	srand(static_cast<unsigned int>(time(0)));
	int value = rand() % 6 + 1;
	value += rand() % 6 + 1;
	return value;
}

int Game::rollDie()
{
	srand(static_cast<unsigned int>(time(0)));
	int value;
	value = rand() % 6 + 1;
	return value;
}

/*
string Game::getInputFromUser(Human &user, string a_inputType) {
	bool validInput = false;
	string userChoice;
	//loop until valid input is entered
	while (validInput == false) {
		cin >> userChoice;
		//Make all characters in userChoice string uppercase
		for (int index = 0; index < int(userChoice.length()); index++) {
			userChoice.at(index) = toupper(userChoice.at(index));
		}
		//Validate input
		validInput = user.verifyInput(userChoice, a_inputType);
		if (validInput == false) {
			cout << "Invalid input try again." << endl;
		}
	}
	return userChoice;
}
*/

int main() {
	int temp;
	cout << "Enter number of rows that you'd like:";
	cin >> temp;
	Game myGame = Game(temp);
	Human player = myGame.m_human;
	Computer CPU = myGame.m_computer;
	//Board board = Board(temp);
	BoardView playerBoardView = BoardView(player, CPU, myGame.m_board);
	//BoardView CPUBoardView = BoardView(CPU);
	playerBoardView.refreshDisplay();
	playerBoardView.display();
	//CPUBoardView.Display();
	player.setCoverSquare(player,5);
	//playerBoardView.refreshDisplay();
	playerBoardView.display();
	playerBoardView.displayScore();
	player.addScore();
	playerBoardView.display();
	playerBoardView.displayScore();

	//m_firstPlayer = 
	

	/*
	map<string, bool> hi = map<string, bool>();
	hi.insert(pair<string,bool>("hi", false));
	hi["hi"] = true;
	cout << hi["hi"];
	*/

	/*
	float progress = 0.0;
	while (progress < 1.0) {
		int barWidth = 70;

		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
		Sleep(50);
		progress += 0.16; // for demonstration only
	}
	std::cout << std::endl;
	*/

	return 0;
}
