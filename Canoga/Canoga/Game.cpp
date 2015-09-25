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
#include <regex>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <queue>
using namespace std;

Game::Game()
{
}


Game::Game(Human& a_human, Computer& a_computer)
{
	m_human = &a_human;
	m_computer = &a_computer;
	struct Computer::Moves m_moves;
	m_firstPlay = true;
	m_gameStarted = false;
	m_isLoaded = false;
	m_diceFile = false;
	m_didHumanMove = false;
	m_didComputerMove = false;
	//askGameRule();

	//setGameRule(m_gameRule);

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
		m_human->setGameRule(m_gameRule);
		if (system("CLS")) system("clear");
		cout << "Game rule has been set to: " + a_gameRule + " squares per row.\n" << endl;
		return true;
	}
}

bool Game::setGameRule(int a_gameRule)
{
	if (a_gameRule != 9 && a_gameRule != 10 && a_gameRule != 11) {
		cerr << "\nNumber of squares must be either 9, 10, or 11." << endl;
		return false;
	}
	else {
		m_gameRule = a_gameRule;
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
	if (a_player.getPlayerType() == "Human")
	{
		m_human->setIsWon();

	}
	if (a_player.getPlayerType() == "Computer")
	{
		m_computer->setIsWon();

	}
}

bool Game::isFirstPlay()
{
	if (m_firstPlay) return true;
	else return false;
}

void Game::setIsFirstPlay()
{
	m_firstPlay = !m_firstPlay;
}

void Game::loadDiceFile()
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

void Game::setLoadedRound(vector<string> a_computerRow, vector<string> a_humanRow) {
	m_board = Board(m_gameRule);
	m_human->setConnectedBoard(m_board);
	m_computer->setConnectedBoard(m_board);
	m_playerDiceSum = 0;
	m_computerDiceSum = 0;
	m_firstPlay = false;
	m_didHumanMove = true;
	m_didComputerMove =true;
	//m_human->setGameRule(m_gameRule);

	if (m_human->getAdvantage() != 0) {
		m_human->setCoverSquare(m_human->getAdvantage());
	}
	if (m_computer->getAdvantage() != 0) {
		m_computer->setCoverSquare(m_computer->getAdvantage());
	}

	for (int i = 0; i < a_computerRow.capacity(); i++) {
		if (a_computerRow.at(i) == "*") {
			m_computer->setCoverSquare(i+1);
		}
	}
	for (int i = 0; i < a_humanRow.capacity(); i++) {
		if (a_humanRow.at(i) == "*") {
			m_human->setCoverSquare(i+1);
		}
	}
}


void Game::setNewRound()
{
	m_board = Board(m_gameRule);
	m_human->setConnectedBoard(m_board);
	m_computer->setConnectedBoard(m_board);
	m_human->addScore(0);
	m_computer->addScore(0);
	m_playerDiceSum = 0;
	m_computerDiceSum = 0;
	//m_human->setGameRule(m_gameRule);

	if (m_human->getAdvantage() != 0) {
		m_human->setCoverSquare(m_human->getAdvantage());
	}
	if (m_computer->getAdvantage() != 0) {
		m_computer->setCoverSquare(m_computer->getAdvantage());
	}
}

void Game::askGameRule()
{
	cout << "Set the rule of the game.\nHow many squares would you like the game boards to have?" << endl;
	cout << "Enter either 9, 10, or 11 as a value: ";
}

void Game::askSaveGame()
{
	cout << endl;
	cout << "Would you like to save your game?" << endl;
	cout << "Type 'yes' to save, or 'no' to keep playing: ";
}

Player* Game::getWinner()
{
	if (m_human->isWon()) return m_human;
	else return m_computer;
}

Player * Game::getFirstPlayer()
{
	if (m_human->getWentFirst()) return m_human;
	if (m_computer->getWentFirst()) return m_computer;
}

Board* Game::getBoardObjet()
{
	return &m_board;
}

BoardView* Game::getBoardViewObject()
{
	return &m_boardView;
}


bool Game::playRound()
{
	int winHumanRowCounter = 0;
	int winComputerRowCounter = 0;
	for (int i = 1; i <= m_gameRule; i++) {
		if (m_human->getBoard()->getHumanRows()->at(i) == true) {
			winHumanRowCounter++;
		}
		if (winHumanRowCounter == m_gameRule) {
			cout << "You covered all your squares! You win!" << endl;
			setWon(*m_human);
			m_human->setWonByCover();
			return true;
		}
		if (m_human->getBoard()->getComputerRows()->at(i) == false) {
			winComputerRowCounter++;
		}
		//dont forget to add if not on first play
		if (winComputerRowCounter == m_gameRule && !isFirstPlay() && m_didComputerMove) {
			cout << "You uncovered all computer's squares! You win!" << endl;
			setWon(*m_human);
			m_human->setWonByUncover();
			return true;
		}
	}



	winHumanRowCounter = 0;
	winComputerRowCounter = 0;
	for (int i = 1; i <= m_gameRule; i++) {
		if (m_computer->getBoard()->getHumanRows()->at(i) == false) {
			winHumanRowCounter++;
		}
		if (winHumanRowCounter == m_gameRule && !isFirstPlay() && m_didHumanMove) {
			cout << "All your squares were uncovered! Computer wins!" << endl;
			setWon(*m_computer);
			m_computer->setWonByUncover();
			return true;
		}
		if (m_human->getBoard()->getComputerRows()->at(i) == true) {
			winComputerRowCounter++;
		}
		//dont forget to add if not on first play
		if (winComputerRowCounter == m_gameRule) {
			cout << "Computer covered all of its squares! Computer wins!" << endl;
			setWon(*m_computer);
			m_computer->setWonByCover();
			return true;
		}
	}



	if (m_human->isTurn()) {
		m_didHumanMove = false;
		m_human->setOneDieMode(false);

		int dieModeCounter = 0;
		for (int i = 7; i <= m_gameRule; i++) {
			if (m_human->getBoard()->getHumanRows()->at(i) == true) {
				dieModeCounter++;
			}
		}
		if (dieModeCounter == ((m_gameRule + 1) - 7))
		{
			m_human->setOneDieMode(true);
		}

		if (!m_diceFile) {
			cout << "Your turn!" << endl;
			cout << "Enter 'roll' to roll the dice: ";
			getInputFromUser(*m_human, "roll");

			if (m_human->isOneDieMode()) {
				cout << "Roll 'one' or 'two' dice?: ";
				string rollChoice;
				rollChoice = getInputFromUser(*m_human, "rollchoice");
				if (rollChoice == "one") {
					m_playerDiceSum = rollDie(*m_human);
				}
				else if (rollChoice == "two") {
					m_playerDiceSum = rollDice(*m_human);
				}
			}
			else {
				m_playerDiceSum = rollDice(*m_human);
			}
		}
		else if (m_diceFile) {
			m_playerDiceSum = m_diceRolls.front();
			m_diceRolls.pop();
		}

		bool coverMoveOpen = false;
		bool uncoverMoveOpen = false;

		m_computerMoves = m_computer->setBestMove(*m_human, *m_computer, m_gameRule, m_playerDiceSum);


		/*
		// maybe do the check for if move is makeable here?
		for (int i = 1; i <= m_board.getMaxSquares(); i++) {
			if (m_human->isCoverable(*m_human, i)) {
				if (m_playerDiceSum == i) {
					coverMoveOpen = true;
				}
			}
			if (m_human->isUncoverable(*m_computer, i)) {
				if (m_playerDiceSum == i) {
					uncoverMoveOpen = true;
				}
			}
			for (int j = i + 1; j <= m_board.getMaxSquares(); j++) {
				if (m_human->isCoverable(*m_human, i)) {
					if (m_human->isCoverable(*m_human, j)) {
						if (m_playerDiceSum == (i + j)) {
							coverMoveOpen = true;
						}
					}
				}
				if (m_human->isUncoverable(*m_computer, i)) {
					if (m_human->isUncoverable(*m_computer, j)) {
						if (m_playerDiceSum == (i + j)) {
							uncoverMoveOpen = true;
						}
					}
				}
				for (int k = j + 1; k <= m_board.getMaxSquares();k++) {
					if (m_human->isCoverable(*m_human, i)) {
						if (m_human->isCoverable(*m_human, j)) {
							if (m_human->isCoverable(*m_human, k)) {
								if (m_playerDiceSum == (i + j + k)) {
									coverMoveOpen = true;
								}
							}
						}
					}
					if (m_human->isUncoverable(*m_computer, i)) {
						if (m_human->isUncoverable(*m_computer, j)) {
							if (m_human->isUncoverable(*m_computer, k)) {
								if (m_playerDiceSum == (i + j + k)) {
									uncoverMoveOpen = true;
								}
							}
						}
					}

					for (int q = k + 1; q <= m_board.getMaxSquares();q++) {
						if (m_human->isCoverable(*m_human, i)) {
							if (m_human->isCoverable(*m_human, j)) {
								if (m_human->isCoverable(*m_human, k)) {
									if (m_human->isCoverable(*m_human, q)) {
										if (m_playerDiceSum == (i + j + k + q)) {
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
										if (m_playerDiceSum == (i + j + k + q)) {
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

		*/
		string input = "";
		do {
			cout << "\n";
			if (m_computerMoves.m_isCoverMove && !m_computerMoves.m_isUncoverMove) {
				cout << "You can only cover your board!" << endl;
				cout << "Type 'cover' to start making selections or ask for 'help': ";
				input = getInputFromUser(*m_human, "cover");
			}
			else if (!m_computerMoves.m_isCoverMove && m_computerMoves.m_isUncoverMove) {
				cout << "You can only uncover the computers board" << endl;
				cout << "Type 'uncover' to start making selections or ask for 'help': ";
				input = getInputFromUser(*m_human, "uncover");
			}
			else if (m_computerMoves.m_isCoverMove && m_computerMoves.m_isUncoverMove) {
				cout << "Would you like to cover or uncover? or ask for 'help': ";
				input = getInputFromUser(*m_human, "coveruncover");
			}
			else if (!m_computerMoves.m_isCoverMove && !m_computerMoves.m_isUncoverMove) {
				cout << "No moves available. Ending turn..." << endl;
				Sleep(1000);
				return false;
			}

			m_boardView.display();

			if (input == "help" && (m_computerMoves.m_isCoverMove || m_computerMoves.m_isUncoverMove)) {
				m_computerMoves = m_computer->setBestMove(*m_human, *m_computer, m_gameRule, m_playerDiceSum);
				if (m_computerMoves.m_isCoverMove) {
					cout << "You should cover your own squares." << endl;
					for (int i = 0; i <= m_computerMoves.m_coverMoveSet.size() - 1; i++) {
						if (m_computerMoves.m_coverMoveSet.at(i) != 0) {
							cout << "You should cover square #" << m_computerMoves.m_coverMoveSet.at(i) << " on your row." << endl;
						}
					}
					continue;
				}

				if (m_computerMoves.m_isUncoverMove) {
					cout << "You should uncover computer's squares." << endl;
					for (int i = 0; i <= m_computerMoves.m_uncoverMoveSet.size() - 1; i++) {
						if (m_computerMoves.m_uncoverMoveSet.at(i) != 0) {
							cout << "You should uncover sqaure #" << m_computerMoves.m_uncoverMoveSet.at(i) << " on computer's side." << endl;
						}

					}
					continue;
				}
			}
		} while (input == "help");
		if (input == "cover" && m_computerMoves.m_isCoverMove) {
			cout << "You picked to cover your row!" << endl;
			cout << "Select the squares you'd like to cover.\nOnce done selecting, type '-1'" << endl;
			cout << "Dice Sum: " << m_playerDiceSum << endl;
		}

		if (input == "uncover" && m_computerMoves.m_isUncoverMove) {
			cout << "You picked to uncover the computer's row!" << endl;
			cout << "Select the squares you'd like to uncover.\nOnce done selecting, type '-1'" << endl;
			cout << "Dice Sum: " << m_playerDiceSum << endl;
		}

		int selection = 0;
		int selectionSum = 0;
		bool valid = false;
		bool invalidTotal = false;
		bool invalidNumbers = false;
		do {
			valid = false;
			invalidTotal = false;
			invalidNumbers = false;
			string selectionInput = "";
			int selections[4] = { 0 };
			selection = 0;
			selectionSum = 0;

			while (selection < 4 && selectionInput != "-1") {
				selectionInput = getInputFromUser(*m_human, "number");
				if (selectionInput != "-1") {
					selections[selection] = stoi(selectionInput);
					//add sum of selection numbers to a variable for later comparison
					// with sum of pips
					selectionSum += selections[selection];
					selection++;
				}
			}

			//check if all selections are equal to the sum of the pips thrown

			// TODO: implement that two selections can't be equal
			// like if i rolled 4..  i can't pick to cover 2 twice


			for (int i = 0; i < selection - 1; i++)
			{
				for (int j = i + 1;j < selection; j++)
				{
					// then this is a duplicate 
					if (selections[i] == selections[j] && selections[i] != 0 && selections[j] != 0) {
						invalidNumbers = true;
						cerr << "Can't insert the same number as multiple selections. Select Again." << endl;
						break;
					}
				}
			}
			// DONE: What if player decided to cover.. but there are no more squares to cover... and he already rolled
			// well.. you gotta reverse the operation.. so go to uncover.. and if also no moves there.. just end round


			if (selectionSum != m_playerDiceSum) {
				invalidTotal = true;
				cerr << "Sum of squares selected does not equal sum of pips.\nSelect again." << endl;
			}
			else {
				invalidTotal = false;
			}

			//check if they are coverable
			if (!invalidTotal && !invalidNumbers) {
				// check if they are coverable only if sum of pips equals sum of selection
				for (int i = 0; i < selection; i++) {
					if (input == "cover") {
						if (m_human->isCoverable(*m_human, selections[i])) {
							valid = true;
						}
						else {
							valid = false;
							cerr << "Cannot cover square #" << selections[i] << " because it is already covered.\nSelect again." << endl;
							break;
						}
					}
					if (input == "uncover") {
						if (m_human->isUncoverable(*m_computer, selections[i])) {
							valid = true;
						}
						else {
							valid = false;
							cerr << "Cannot uncover square #" << selections[i] << " because it is not covered.\nSelect again." << endl;
							break;
						}
					}
				}

				// if all selections are valid, start covering
				if (valid && !invalidTotal && !invalidNumbers) {
					for (int i = 0; i < selection; i++) {
						if (input == "cover") {
							m_human->setCoverSquare(selections[i]);
							cout << "Square #" << selections[i] << " on your row has been covered" << endl;
						}
						if (input == "uncover") {
							m_computer->setUncoverSquare(selections[i]);
							cout << "Square #" << selections[i] << " on computer's row has been uncovered" << endl;
						}
					}
					return true;
				}
			}
		} while (!valid || invalidTotal || invalidNumbers);
	}
	else {
		cout << "\n";
		m_didComputerMove = false;
		// can we use one die?
		int dieModeCounter = 0;
		for (int i = 7; i <= m_gameRule; i++) {
			if (m_computer->getBoard()->getComputerRows()->at(i) == true) {
				dieModeCounter++;
			}
		}
		if (dieModeCounter == ((m_gameRule + 1) - 7))
		{
			m_computer->setOneDieMode(true);
		}

		int squareDieCounter = 0;
		for (int i = 1; i <= 4; i++) {
			if (m_computer->isCoverable(*m_computer, i)) {
				squareDieCounter++;
			}
		}
		if (!m_diceFile) {
			if (squareDieCounter == 4 && m_computer->isOneDieMode()) {
				m_computerDiceSum = rollDie(*m_computer);
			}
			else {
				m_computerDiceSum = rollDice(*m_computer);
			}
		}
		if (m_diceFile) {
			m_computerDiceSum = m_diceRolls.front();
			m_diceRolls.pop();
		}
		m_computerMoves = m_computer->setBestMove(*m_computer, *m_human, m_gameRule, m_computerDiceSum);



		if (!m_computerMoves.m_isUncoverMove && !m_computerMoves.m_isCoverMove) {
			cout << "No move made by computer." << endl;
			cout << "Ending turn..." << endl;
			Sleep(1000);
			return false;
		}
		if (m_computerMoves.m_isCoverMove) {
			cout << "Computer decided to cover own squares." << endl;
			for (int i = 0; i <= m_computerMoves.m_coverMoveSet.size() - 1; i++) {
				if (m_computerMoves.m_coverMoveSet.at(i) != 0) {
					m_computer->setCoverSquare(m_computerMoves.m_coverMoveSet.at(i));
					cout << "Computer covered square #" << m_computerMoves.m_coverMoveSet.at(i) << " on it's own row." << endl;
				}

			}
			return true;
		}

		if (m_computerMoves.m_isUncoverMove) {
			cout << "Computer decided to uncover your squares." << endl;
			for (int i = 0; i <= m_computerMoves.m_uncoverMoveSet.size() - 1; i++) {
				if (m_computerMoves.m_uncoverMoveSet.at(i) != 0) {
					m_human->setUncoverSquare(m_computerMoves.m_uncoverMoveSet.at(i));
					cout << "Computer uncovered square #" << m_computerMoves.m_uncoverMoveSet.at(i) << " on your row." << endl;
				}
			}
			return true;
		}
	}
}


void Game::setFirstPlayer()
{
	while (m_playerDiceSum == m_computerDiceSum) {
		if (!m_diceFile) {
			m_playerDiceSum = rollDice(*m_human);
			//cout << "You rolled a " << m_playerDiceSum << endl;
			//Sleep(2000);
			m_computerDiceSum = rollDice(*m_computer);
		}
		else if (m_diceFile) {
			m_playerDiceSum = m_diceRolls.front();
			m_diceRolls.pop();
			m_computerDiceSum = m_diceRolls.front();
			m_diceRolls.pop();
		}
		//cout << "Computer rolled a " << m_computerDiceSum << endl;
		if (m_playerDiceSum == m_computerDiceSum) {
			cout << "You and the computer both rolled a " << m_playerDiceSum << endl;
			cout << "Rolling again..." << endl;
		}
		else if (m_playerDiceSum > m_computerDiceSum) {
			m_firstPlayer = m_human;
			m_human->setTurn();
			m_human->setWentFirst(true);
			m_computer->setWentFirst(false);
			cout << "You are going first!" << endl;
		}
		else if (m_computerDiceSum > m_playerDiceSum) {
			m_firstPlayer = m_computer;
			m_computer->setTurn();
			m_computer->setWentFirst(true);
			m_human->setWentFirst(false);
			cout << "Computer is going first!" << endl;
		}
	}
}

bool Game::saveGame() {
	ofstream myFile;
	//Get file name from user
	cout << "What would you like to name the file?  Max 30 characters please." << endl;
	cout << "Enter 'back' to go back." << endl;
	string input = getInputFromUser(*m_human, "filename");
	if (input == "back") {
		return false;
	}

	input = input + ".txt";
	try {
		myFile.open(input);

		myFile << "Computer:" << endl;
		//Write computer squares to file
		myFile << "\tSquares: ";
		for (int i = 1; i <= m_gameRule; i++) {
			if (m_computer->isCoverable(*m_computer,i)) {
				myFile << i << " ";
			}
			if (!m_computer->isCoverable(*m_computer, i)) {
				myFile << "* ";
			}
		}
		myFile << endl;
		//Write computer's score
		myFile << "\tScore:" << m_computer->getScore();
		myFile << endl;
		myFile << endl;


		//human stats
		myFile << "Human:" << endl;
		//Write human's squares
		myFile << "\tSquares: ";
		for (int i = 1; i <= m_gameRule; i++) {
			if (m_human->isCoverable(*m_human, i)) {
				myFile << i << " ";
			}
			if (!m_human->isCoverable(*m_human, i)) {
				myFile << "* ";
			}
		}
		myFile << endl;
		//Write human's score
		myFile << "\tScore:" << m_human->getScore();
		myFile << endl;
		myFile << endl;

		myFile << "First Turn: " << getFirstPlayer()->getPlayerType() << endl;
		myFile << "Next Turn: ";
		if (m_human->isTurn()) {
			myFile << "Human" << endl;
		}
		else if (m_computer->isTurn()) {
			myFile << "Computer" << endl;
		}
		myFile.close();
		return true;
	}
	catch (exception const& e) {
		cerr << "Error " << e.what() << endl;
		return false;
	}
}

bool Game::isGameStarted() {
	return m_gameStarted;
}

bool Game::isLoaded()
{
	return m_isLoaded;
}

void Game::setIsLoaded(bool a_flag)
{
	m_isLoaded = a_flag;
}

int Game::rollDice(Player& a_player)
{
	Sleep(2000);
	srand(static_cast<unsigned int>(time(0)));
	//srand(time(NULL));
	int value = 0;
	int value1 = rand() % 6 + 1;
	int value2 = rand() % 6 + 1;
	value = value1 + value2;
	cout << a_player.getPlayerType() << " rolled a " << value1 << " and a " << value2 << ". A total of " << value << "." << endl;
	return value;
}

int Game::rollDie(Player& a_player)
{
	Sleep(2000);
	srand(static_cast<unsigned int>(time(0)));
	//srand(time(NULL));
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

bool Game::playGame(int a_roundNumber) {
	if (m_diceFile) {
		loadDiceFile();
	}

	string input;
	cout << "Begin round #" << a_roundNumber << " !\n" << endl;

	if (!isLoaded()) {
		askGameRule();
		input = getInputFromUser(*m_human, "gamerule");
		setGameRule(input);

		//myGame.setGameRule(temp);

		setNewRound();
	}
	m_boardView = BoardView(*m_human, *m_computer, m_board);
	m_gameStarted = true;

	if (!isLoaded() && !m_diceFile) {
		cout << "Time to roll the dice to see who goes first!" << endl;
		cout << "Type 'roll' to roll the dice: ";
		getInputFromUser(*m_human, "roll");
	}

	m_boardView.refreshDisplay();
	m_boardView.display();
	m_boardView.displayScore();
	if (!isLoaded()) {
		setFirstPlayer();
	}

	while (!isWon()) {
		if (isFirstPlay()) {
			//m_boardView.display();
			//m_boardView.displayScore();
			//m_boardView.displayTurns();

			//myGame.m_human->setCoverSquare(1);
			if (!playRound()) {
				m_human->setTurn();
				m_computer->setTurn();
				setIsFirstPlay();
				askSaveGame();
				input = getInputFromUser(*m_human, "save");
				if (input == "yes") {
					saveGame();
					m_boardView.display();
					m_boardView.displayScore();
					m_boardView.displayTurns();
					cout << "Game Saved! Quitting game..." << endl;
					return false;
				}
			}
			m_boardView.display();
			//m_boardView.displayScore();
			m_boardView.displayTurns();

			//myGame.setWon(*myGame.m_human);

		}
		else {
			if (!playRound()) {
				m_human->setTurn();
				m_computer->setTurn();
				askSaveGame();
				input = getInputFromUser(*m_human, "save");
				if (input == "yes") {
					saveGame();
					m_boardView.display();
					m_boardView.displayScore();
					cout << "Game Saved! Quitting game..." << endl;
					return false;
				}
			}
			m_boardView.display();
			//m_boardView.displayScore();
			m_boardView.displayTurns();
		}

		if (isWon()) {
			if (getWinner()->getPlayerType() == "Human") {
				//TODO: implement score calculations
				//sum of all uncovered squares of computer
				//cout << "You win!" << endl;
				int scoreSum = 0;
				m_human->setIsWon();
				if (m_human->getWonBy() == "cover") {
					for (int i = 1; i <= getGameRule(); i++) {
						if (m_human->isCoverable(*m_computer, i)) {
							scoreSum += i;
						}
					}
					m_human->addScore(scoreSum);
					m_human->setRoundScore(scoreSum);
					m_human->addWin();
				}
				else if (m_human->getWonBy() == "uncover") {
					for (int i = 1; i <= getGameRule(); i++) {
						if (m_human->isUncoverable(*m_human, i)) {
							scoreSum += i;
						}
					}
					m_human->addScore(scoreSum);
					m_human->setRoundScore(scoreSum);
					m_human->addWin();
				}

			}
			else if (getWinner()->getPlayerType() == "Computer") {
				//TODO: implement score calculations
				//sum of all uncovered squares of computer
				//cout << "You lose!" << endl;
				int scoreSum = 0;
				m_computer->setIsWon();
				if (m_computer->getWonBy() == "cover") {
					for (int i = 1; i <= getGameRule(); i++) {
						if (m_computer->isCoverable(*m_human, i)) {
							scoreSum += i;
						}
					}
					m_computer->addScore(scoreSum);
					m_computer->setRoundScore(scoreSum);
					m_computer->addWin();
				}
				else if (m_computer->getWonBy() == "uncover") {
					for (int i = 1; i <= getGameRule(); i++) {
						if (m_computer->isUncoverable(*m_computer, i)) {
							scoreSum += i;
						}
					}
					m_computer->addScore(scoreSum);
					m_computer->setRoundScore(scoreSum);
					m_computer->addWin();
				}
			}
			m_boardView.displayScore();
		}
	}
}
