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


Game::Game(Human& a_human, Computer& a_computer)
{
	m_human = &a_human;
	m_computer = &a_computer;
	//askGameRule();

	//setGameRule(a_gameRule);
	
	//setNewRound();
}


Game::~Game()
{
}

int Game::getGameRule()
{
	return m_gameRule;
}

bool Game::setGameRule(string a_gameRule)
{
	int selection;
	try {
		selection = stoi(a_gameRule);
	}
	catch (invalid_argument) {
		return false;
	}
	if (selection != 9 && selection != 10 && selection != 11) {
		cerr << "\nNumber of squares must be either 9, 10, or 11." << endl;
		return false;
	}
	else 
	{
		m_gameRule = selection;
		cout << "Game rule has been set to: " + a_gameRule + " squares per row." << endl;
		return true;
	}
}

void Game::setNewRound()
{
	m_board = Board(m_gameRule);
	m_human->setConnectedBoard(m_board);
	m_computer->setConnectedBoard(m_board);
	m_human->setScore(0);
	m_computer->setScore(0);
	m_playerDiceSum = 0;
	m_computerDiceSum = 0;
}

void Game::askGameRule()
{
	cout << "Set the rule of the game.\nHow many squares would you like the game boards to have?" << endl;
	cout << "Enter either 9, 10, or 11 as a value: ";
}

Player* Game::getWinner()
{
	if (m_human->isWon()) return m_human;
	else return m_computer;
}


void Game::playRound()
{
	if (m_human->isTurn()) {
		askMove();
	}
	else {
		m_computer->searchAndDestroy(); 
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
			m_firstPlayer = *m_human;
			m_human->setTurn();
		}
		if (m_computerDiceSum > m_playerDiceSum) {
			m_firstPlayer = *m_computer;
			m_computer->setTurn();
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
	bool valid, play;
	string input;
	Human player = Human();
	do {


		cout << "Would you like to play a game?" << endl;
		cout << "Commands: 'Play' | 'Quit'" << endl;
		cout << "Selection: ";
		cin >> input;
		valid = player.verifyInput(input, "start");
		if (valid == true) {
			if (player.toLowerCase(input) == "play") {
				play = true;
			}
			else {
				play = false;
				cout << "Quitting the game..." << endl;
			}
		}
		else {
			cout << "Invalid Input." << endl;
		}
	} while (!valid);
	if(play){
		cout << "Let's play Canoga!" << endl;
		if (system("CLS")) system("clear");
		Computer CPU = Computer();
		Game myGame = Game(player, CPU);
		myGame.askGameRule();
		cin >> input;
		//myGame.setGameRule(temp);

		while (myGame.setGameRule(input) == false) {
			cout << "Try again ('Q' to Quit): ";
			cin >> input;
		}
		myGame.setNewRound();


		//Board board = Board(temp);
		BoardView playerBoardView = BoardView(player, CPU, myGame.m_board);
		//BoardView CPUBoardView = BoardView(CPU);
		//playerBoardView.refreshDisplay();
		playerBoardView.display();
		//CPUBoardView.Display();
		player.setCoverSquare(player, 5);
		//playerBoardView.refreshDisplay();
		playerBoardView.display();
		//playerBoardView.displayScore();
		player.addScore();
		playerBoardView.display();
		playerBoardView.displayScore();
	}
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
