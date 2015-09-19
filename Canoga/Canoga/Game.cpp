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
#include <thread>

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
		cout << "Game rule has been set to: " + a_gameRule + " squares per row.\n" << endl;
		return true;
	}
}

bool Game::isWon()
{
	if (m_human->isWon() || m_computer->isWon()) return true;
	else return false;
}

void Game::setWon(Player& a_player)
{
	if (a_player.getPlayerType() == "Human") m_human->setIsWon();
	if (a_player.getPlayerType() == "Computer") m_computer->setIsWon();
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
		cout << "Type 'roll' to roll the dice" << endl;
		getInputFromUser(*m_human, "roll");
		m_playerDiceSum = rollDice(*m_human);
		

		bool coverMoveOpen = false;
		bool uncoverMoveOpen = false;

		// maybe do the check for if move is makeable here?
		for (int i = 0; i < m_board.getMaxSquares(); i++) {
			if (m_human->isCoverable(*m_human, i)) {
				if (m_playerDiceSum = i) {
					coverMoveOpen = true;
				}
			}
			if (m_human->isUncoverable(*m_computer, i)) {
				if (m_playerDiceSum = i) {
					uncoverMoveOpen = true;
				}
			}
			for (int j = 0; j < m_board.getMaxSquares(); j++) {
				if (m_human->isCoverable(*m_human, i)) {
					if (m_human->isCoverable(*m_human, j)) {
						if ( m_playerDiceSum == (i + j)) {
							coverMoveOpen = true;
						}
					}
				}
				if (m_human->isUncoverable(*m_computer, i)) {
					if (m_human->isUncoverable(*m_computer, i)) {
						if (m_playerDiceSum == (i + j)) {
							uncoverMoveOpen = true;
						}
					}
				}
				for (int k = 0; k < m_board.getMaxSquares();k++) {
					if (m_human->isCoverable(*m_human, i)) {
						if (m_human->isCoverable(*m_human, j)) {
							if (m_human->isCoverable(*m_human, k)) {
								if (m_playerDiceSum == (i+j+k)) {
									coverMoveOpen = true;
								}
							}
						}
					}
					if (m_human->isUncoverable(*m_computer, i)) {
						if (m_human->isUncoverable(*m_computer, j)) {
							if (m_human->isUncoverable(*m_computer, k)) {
								if (m_playerDiceSum == (i+j+k)) {
									uncoverMoveOpen = true;
								}
							}
						}
					}

					for (int q = 0; q < m_board.getMaxSquares();q++) {
						if(m_human->isCoverable(*m_human,i )){
							if (m_human->isCoverable(*m_human, j)) {
								if (m_human->isCoverable(*m_human, k)) {
									if (m_human->isCoverable(*m_human, q)) {
										if (m_playerDiceSum == (i+j+k+q)) {
											coverMoveOpen = true;
										}
									}
								}
							}
						}
						if (m_human->isUncoverable(*m_computer, i)) {
							if (m_human->isUncoverable(*m_computer, j)) {
								if (m_human->isUncoverable(*m_computer, k)) {
									if (m_human->isUncoverable(*m_computer, q)) {
										if (m_playerDiceSum == (i+j+k+q)) {
											uncoverMoveOpen = true;
										}
									}
								}
							}
						}

					}
				}
			}
		}
		string input = "";
		if (coverMoveOpen && !uncoverMoveOpen) {
			cout << "You can cover your board!" << endl;
			cout << "Type 'cover' to start making selections:" << endl;
			input = getInputFromUser(*m_human, "cover");
			
		}
		else if (uncoverMoveOpen && !coverMoveOpen) {
			cout << "You can only uncover the computers board" << endl;
			cout << "Type 'uncover' to start making selections:" << endl;
			input = getInputFromUser(*m_human, "uncover");
		}
		else if (coverMoveOpen && uncoverMoveOpen) {
			cout << "Would you like to cover or uncover?";
			cout << "Type 'cover' to cover your squares or 'uncover' to uncover the computer's squares:" << endl;
		}








		//string input = getInputFromUser(*m_human, "side");
		if ( input == "cover") {
			cout << "You picked to cover your row!" << endl;
			cout << "Select the squares you'd like to cover.\nOnce done selecting, type '-1'" << endl;
			int selection = 0;
			int selections[4];
			int selectionSum = 0;
			bool valid = false;
			bool validTotal = false;
			while (!valid && !validTotal) {
				string selectionInput = "";
				selection = 0;
				while (selection < 4 && selectionInput != "-1") {
					selectionInput = getInputFromUser(*m_human, "number");
					if (selectionInput != "-1") {
						selections[selection] = stoi(selectionInput);
						selection++;
					}
				}

				//check if all selections are equal to the sum of the pips thrown

				// TODO: implement that two selections can't be equal
				// like if i rolled 4..  i can't pick to cover 2 twice

				// What if player decided to cover.. but there are no more squares to cover... and he already rolled
				// well.. you gotta reverse the operation.. so go to uncover.. and if also no moves there.. just end round



				for (int i = 0; i < selection; i++) {
					selectionSum += selections[i];
				}

				if (selectionSum != m_playerDiceSum) {
					validTotal = false;
					cout << "Sum of squares selected does not equal sum of pips.\nSelect again." << endl;
				}
				else {
					validTotal = true;
				}

				//check if they are coverable
				if (validTotal) {
					// check if they are coverable only if sum of pips equals sum of selection
					for (int i = 0; i < selection; i++) {
						if (m_human->isCoverable(*m_human, selections[i])) {
							valid = true;
						}
						else {
							valid = false;
							cout << "Cannot cover square #" << selections[i] << " because it is already covered.\nSelect again." << endl;
							break;
						}
					}
					
					// if all selections are valid, start covering
					if (valid) {
						for (int i = 0; i < selection; i++) {
							m_human->setCoverSquare(selections[i]);
							cout << "Square #" << selections[i] << " on the computer's row has been covered" << endl;
						}
					}
				}
			}

		}
		else if (input == "uncover") {
			cout << "You picked to uncover the computer's row!" << endl;
			cout << "Select the squares you'd like to uncover.\n Once done selecting, type '-1'" << endl;
		}
		
	}
	else {
		m_computerDiceSum = rollDice(*m_computer);
		m_computer->searchAndDestroy(); 
	}
}


void Game::setFirstPlayer()
{
	while (m_playerDiceSum == m_computerDiceSum) {

		m_playerDiceSum = rollDice(*m_human);
		//cout << "You rolled a " << m_playerDiceSum << endl;
		Sleep(2000);
		m_computerDiceSum = rollDice(*m_computer);
		//cout << "Computer rolled a " << m_computerDiceSum << endl;
		if (m_playerDiceSum == m_computerDiceSum) {
			cout << "You and the computer both rolled a " << m_playerDiceSum << endl;
			cout << "Rolling again..." << endl;
		}
		else if (m_playerDiceSum > m_computerDiceSum) {
			m_firstPlayer = *m_human;
			m_human->setTurn();
			m_human->setWentFirst();
			cout << "You are going first!" << endl;
		}
		else if (m_computerDiceSum > m_playerDiceSum) {
			m_firstPlayer = *m_computer;
			m_computer->setTurn();
			m_computer->setWentFirst();
			cout << "Computer is going first!" << endl;
		}
	}
}


int Game::rollDice(Player& a_player)
{
	//srand(static_cast<unsigned int>(time(0)));
	srand(time(NULL));
	int value = 0;
	int value1 = rand() % 6 + 1;
	int value2 = rand() % 6 + 1;
	value = value1 + value2;
	cout << a_player.getPlayerType() << " rolled a " << value1 << " and a " << value2 << ". A total of " << value << "." << endl;
	return value;
}

int Game::rollDie(Player& a_player)
{
	//srand(static_cast<unsigned int>(time(0)));
	srand(time(NULL));
	int value;
	value = rand() % 6 + 1;
	cout << a_player.getPlayerType() << " rolled a " << value << "." << endl;
	return value;
}


string Game::getInputFromUser(Human &user, string a_inputType) {
	bool validInput = false;
	string userChoice;
	//loop until valid input is entered
	while (validInput == false) {
		cin >> userChoice;
		//Make all characters in userChoice string uppercase
		for (int index = 0; index < int(userChoice.length()); index++) {
			userChoice.at(index) = tolower(userChoice.at(index));
		}
		//Validate input
		validInput = user.verifyInput(userChoice, a_inputType);
		if (validInput == false) {
			cout << "Invalid input try again." << endl;
		}
	}
	return userChoice;
}


int main() {
	bool valid, play, firstPlay;
	firstPlay = true;
	string input;
	Human player = Human();
	do {


		cout << "Would you like to play a game?" << endl;
		cout << "Type 'play' or 'quit'" << endl;
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
		cout << "Let's play Canoga!\n" << endl;
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
		BoardView playerBoardView = BoardView(player, CPU, myGame.m_board);

		while (!myGame.isWon()) {
			if (firstPlay) {
				cout << "Time to roll the dice to see who goes first!" << endl;
				cout << "Type 'roll' to roll the dice" << endl;
				myGame.getInputFromUser(player, "roll");
				playerBoardView.refreshDisplay();
				myGame.setFirstPlayer();
				
				myGame.playRound();

				playerBoardView.display();




				myGame.setWon(*myGame.m_human);
			}
			else {
				myGame.playRound();
			}
		}


		//Board board = Board(temp);

		//BoardView CPUBoardView = BoardView(CPU);
		//playerBoardView.refreshDisplay();

		//CPUBoardView.Display();
		player.setCoverSquare(5);
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
