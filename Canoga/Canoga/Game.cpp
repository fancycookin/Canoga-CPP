/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
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

/* *********************************************************************
Function Name: Game
Purpose: default constructor for Game class
Parameters: none
Return Value:  Game
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Game::Game()
{
}

/* *********************************************************************
Function Name: Game
Purpose: overloaded constructor to assign players to their boards and 
		 intiliaze round flags
Parameters: Human& a_human - Human player object passed by reference from
			Tournment class
			Computer& a_computer - Computer player object passed by reference
			from Tournment class
Return Value: Game
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
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
}

/* *********************************************************************
Function Name:Game
Purpose: Destructor for Game class
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Game::~Game()
{
}

/* *********************************************************************
Function Name: getGameRule
Purpose: get the number of maximum size of squares on the board
Parameters: none
Return Value: int m_gameRule - maximuze size of squares on a players row on
				the board
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
int Game::getGameRule() const
{
	return m_gameRule;
}

/* *********************************************************************
Function Name: getIsDiceFile
Purpose: check if flag for loading a dice file is set
Parameters: none
Return Value: bool m_diceFile - true if needs to be loaded, false if not
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Game::getIsDiceFile() const
{
	return m_diceFile;
}

/* *********************************************************************
Function Name: setIsDiceFile
Purpose: set flag to load dice file to true or false
Parameters: bool a_flag - true or false flag
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Game::setIsDiceFile(bool a_flag)
{
	m_diceFile = a_flag;
}

/* *********************************************************************
Function Name: setGameRule
Purpose: function to set number of maximum size of squares on board
Parameters: string a_gameRule - 
Return Value: returns true if set was succeful, false if not
Local Variables: int selection - variable to hold the number of game rule
Algorithm: Get string which is user input, check the number, validate, then set
			game rule
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: setGameRule
Purpose: Overriden function to use an int parameter instead of string to set
		game rule
Parameters: int a_gameRule - number of maximum size of squares on the board
Return Value: true if succesful, false if faield
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: isWon
Purpose: check if one of the two players won the round
Parameters: none
Return Value: bool - true if a player has one, else false
Local Variables: none
Algorithm: check if one of the players won
			if so, retrun true
			else return false
Assistance Received: none
********************************************************************* */
bool Game::isWon() const
{
	if (m_human->isWon() || m_computer->isWon()) return true;
	else return false;
}

/* *********************************************************************
Function Name: setWon
Purpose: toggle a player's win flag
Parameters: Player& a_player - the player that's flag needs to be toggled
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: isFirstPlay
Purpose: check if this is the first turn being played. this is used to 
		prevent advantage square uncovering
Parameters: none
Return Value: true if is first play, false if it is not
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Game::isFirstPlay() const
{
	if (m_firstPlay) return true;
	else return false;
}

/* *********************************************************************
Function Name: setIsFirstPlay
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
void Game::setIsFirstPlay()
{
	m_firstPlay = !m_firstPlay;
}

/* *********************************************************************
Function Name: setLoadedRound
Purpose: set up players, board, advantage, game flags such as turn, first player, and such
		 when a game is to be loaded
Parameters: vector<string> a_computerRow - the computer's parsed row from  the serialized file
			vector<string> a_humanRow - the parsed human's row from the serialized file
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Game::setLoadedRound(vector<string> a_computerRow, vector<string> a_humanRow) {
	m_board = Board(m_gameRule);
	m_human->setConnectedBoard(m_board);
	m_computer->setConnectedBoard(m_board);
	m_playerDiceSum = 0;
	m_computerDiceSum = 0;
	m_firstPlay = false;
	m_didHumanMove = true;
	m_didComputerMove =true;

	if (m_human->getAdvantage() != 0) {
		m_human->setCoverSquare(m_human->getAdvantage());
	}
	if (m_computer->getAdvantage() != 0) {
		m_computer->setCoverSquare(m_computer->getAdvantage());
	}

	for (int i = 0; i < a_computerRow.size(); i++) {
		if (a_computerRow.at(i) == "*") {
			m_computer->setCoverSquare(i+1);
		}
	}
	for (int i = 0; i < a_humanRow.size(); i++) {
		if (a_humanRow.at(i) == "*") {
			m_human->setCoverSquare(i+1);
		}
	}
}


/* *********************************************************************
Function Name: setNewRound
Purpose: set up players, board, game flags such as turn, first player, and
		such when playing a new game
Parameters: none
Return Value: none
Local Variables: none
Algorithm: create players, connect them to the board, reset scores and points
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: askGameRule
Purpose: prompt user with a message to select game rule
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Game::askGameRule()
{
	cout << "Set the rule of the game.\nHow many squares would you like the game boards to have?" << endl;
	cout << "Enter either 9, 10, or 11 as a value: ";
}

/* *********************************************************************
Function Name: askSaveGame
Purpose: prompt user with a message to offer to save game
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Game::askSaveGame()
{
	cout << endl;
	cout << "Would you like to save your game?" << endl;
	cout << "Type 'yes' to save, or 'no' to keep playing: ";
}

/* *********************************************************************
Function Name: getWinner
Purpose: get winner of a round
Parameters: none
Return Value: Player* - pointer to the player that won
Local Variables: none
Algorithm: check a player's win flag to see if they won
Assistance Received: none
********************************************************************* */
Player* Game::getWinner() const
{
	if (m_human->isWon()) return m_human;
	else return m_computer;
}

/* *********************************************************************
Function Name: getFirstPlayer
Purpose: get the player who went first
Parameters: none
Return Value: Player* - pointed to the player that went first
Local Variables: none
Algorithm: check went first flag for each player then return who had it true
Assistance Received: none
********************************************************************* */
Player * Game::getFirstPlayer() const
{
	if (m_human->getWentFirst()) return m_human;
	if (m_computer->getWentFirst()) return m_computer;
}

/* *********************************************************************
Function Name: getBoardObjet
Purpose: grab the board object
Parameters: none
Return Value: Board* -  pointer to the board object being used by game
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Board* Game::getBoardObjet()
{
	return &m_board;
}

/* *********************************************************************
Function Name:getBoardViewObject
Purpose: grab the BoardView object
Parameters: none
Return Value: BoardView* - pointer to the board view object being used by game
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
BoardView* Game::getBoardViewObject()
{
	return &m_boardView;
}


/* *********************************************************************
Function Name: playRound
Purpose: To play the round of a game
Parameters: none
Return Value: true if a player won, false if nobody won yet and move 
				has been made or no move has been made
		
Local Variables: int WinHumanRowCounter - counter to hold number of covered squares by human
				 int winComputerRowCounter - counter to hold number of uncovered squares by human
				 bool coverMoveOpen - is cover move available flag
				 bool uncoverMoveOpen -  is uncover move avaiable flag
				 string rollChoice - string to hold either choice of one or two dice
				 string input -  variable to hold user's input
				 int selection - variable to hold user's square selection
				 int selectionSum - variable to hold user's square selection sum
				 bool valid - move valid flag
				 bool invalidTotal - invalid sum of selections flag
				 bool invalidNumbers - invalid square selected (uncoverable, or ununcoverable) flag
				 int dieModeCounter - one die counter to check for squares
				 int squareDieCounter - number of squares to one die mode 

Algorithm:		 1) check if human won by covering or uncovering
				 2) check if computer won by covering or uncovering
				 3) if humans turn, ask for input: roll
				 4) ask to roll one or two dice (when applicable)
				 5) offer cover or uncover when applicable
				 6) take in selections
				 7) validate selections
				 8) cover or uncover selections

				 9) check computers turn
				 10) get all possible moves
				 11) determine the best move: cover or uncover
				 12) apply cover or uncover moves
Assistance Received: none
********************************************************************* */
bool Game::playRound()
{
	// check if human won
	int winHumanRowCounter = 0;
	int winComputerRowCounter = 0;
	for (int i = 1; i <= m_gameRule; i++) {
		if (m_human->getBoard()->getHumanRows()->at(i) == true) {
			winHumanRowCounter++;
		}
		// by covering own squares
		if (winHumanRowCounter == m_gameRule) {
			cout << "You covered all your squares! You win!" << endl;
			setWon(*m_human);
			m_human->setWonByCover();
			return true;
		}
		if (m_human->getBoard()->getComputerRows()->at(i) == false) {
			winComputerRowCounter++;
		}
		//by uncovering computer's squares
		if (winComputerRowCounter == m_gameRule && !isFirstPlay() && m_didComputerMove) {
			cout << "You uncovered all computer's squares! You win!" << endl;
			setWon(*m_human);
			m_human->setWonByUncover();
			return true;
		}
	}

	// check if computer won
	winHumanRowCounter = 0;
	winComputerRowCounter = 0;
	for (int i = 1; i <= m_gameRule; i++) {
		if (m_computer->getBoard()->getHumanRows()->at(i) == false) {
			winHumanRowCounter++;
		}
		// by uncovering all humans squares
		if (winHumanRowCounter == m_gameRule && !isFirstPlay() && m_didHumanMove) {
			cout << "All your squares were uncovered! Computer wins!" << endl;
			setWon(*m_computer);
			m_computer->setWonByUncover();
			return true;
		}
		if (m_human->getBoard()->getComputerRows()->at(i) == true) {
			winComputerRowCounter++;
		}
		// by covering all own squares
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
			if (m_human->m_diceRolls.empty()) {
				m_diceFile = false;
			}
			else {
				m_playerDiceSum = m_human->m_diceRolls.front();
				cout << "Dice sum: " << m_playerDiceSum << endl;
				m_human->m_diceRolls.pop();
			}
		}

		bool coverMoveOpen = false;
		bool uncoverMoveOpen = false;

		m_computerMoves = m_computer->setBestMove(*m_human, *m_computer, m_gameRule, m_playerDiceSum, isFirstPlay());

		string input = "";
		do {
			//prompt options
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

			// cover help
			if (input == "help" && (m_computerMoves.m_isCoverMove || m_computerMoves.m_isUncoverMove)) {
				m_computerMoves = m_computer->setBestMove(*m_human, *m_computer, m_gameRule, m_playerDiceSum, isFirstPlay());
				if (m_computerMoves.m_isCoverMove) {
					if (!m_computerMoves.m_isUncoverMove) {
						cout << "You should cover because that's the only move available." << endl;
					}
					else {
						cout << "You should cover your own squares to take control of more squares on the board." << endl;
					}
					for (int i = 0; i <= m_computerMoves.m_coverMoveSet.size() - 1; i++) {
						if (m_computerMoves.m_coverMoveSet.at(i) != 0) {
							cout << "You should cover square #" << m_computerMoves.m_coverMoveSet.at(i) << " on your row." << endl;
						}
					}
					continue;
				}

				// uncover help
				if (m_computerMoves.m_isUncoverMove) {
					if (!m_computerMoves.m_isCoverMove) {
						cout << "You should uncover because that's the only move available." << endl;
					}
					else {
						cout << "You should uncover computer's squares to take control of more squares on the board." << endl;
					}
					for (int i = 0; i <= m_computerMoves.m_uncoverMoveSet.size() - 1; i++) {
						if (m_computerMoves.m_uncoverMoveSet.at(i) != 0) {
							cout << "You should uncover sqaure #" << m_computerMoves.m_uncoverMoveSet.at(i) << " on computer's side." << endl;
						}

					}
					continue;
				}
			}
		} while (input == "help");
		// cover feedback
		if (input == "cover" && m_computerMoves.m_isCoverMove) {
			cout << "You picked to cover your row!" << endl;
			cout << "Select the squares you'd like to cover.\nOnce done selecting, type '-1'" << endl;
			cout << "Dice Sum: " << m_playerDiceSum << endl;
		}
		//uncover feedback
		if (input == "uncover" && m_computerMoves.m_isUncoverMove) {
			cout << "You picked to uncover the computer's row!" << endl;
			cout << "Select the squares you'd like to uncover.\nOnce done selecting, type '-1'" << endl;
			cout << "Dice Sum: " << m_playerDiceSum << endl;
		}
		
		// validate selections
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
			
			// selections input
			while (selection < 4 && selectionInput != "-1") {
				selectionInput = getInputFromUser(*m_human, "number");
				if (selectionInput != "-1") {
					selections[selection] = stoi(selectionInput);
					// add sum of selection numbers to a variable for later comparison
					// with sum of pips
					selectionSum += selections[selection];
					selection++;
				}
			}

			//check if all selections are equal to the sum of the pips thrown
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
			// What if player decided to cover.. but there are no more squares to cover... and he already rolled
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
						if (m_human->isUncoverable(*m_computer, selections[i]) && m_computer->getAdvantage() == selections[i] && isFirstPlay()) {
							valid = false;
							cerr << "Cannot cover square #" << selections[i] << " because it is an advantage square.\nSelect again." << endl;
						}
						else if (m_human->isUncoverable(*m_computer, selections[i])) {
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
		//load from dice file if activated
		if (m_diceFile) {
			if (m_human->m_diceRolls.empty()) {
				m_diceFile = false;
			}
			else {
				m_computerDiceSum = m_human->m_diceRolls.front();
				cout << "Dice sum: " << m_computerDiceSum << endl;
				m_human->m_diceRolls.pop();
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

		m_computerMoves = m_computer->setBestMove(*m_computer, *m_human, m_gameRule, m_computerDiceSum, isFirstPlay());


		// display moves made by computer
		if (!m_computerMoves.m_isUncoverMove && !m_computerMoves.m_isCoverMove) {
			cout << "No move made by computer." << endl;
			cout << "Ending turn..." << endl;
			Sleep(1000);
			return false;
		}
		if (m_computerMoves.m_isCoverMove) {
			cout << "Computer decided to cover own squares." << endl;
			cout << "Computer plays defensively to take control over more squares." << endl;
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
			cout << "Computer plays aggressively to prevent you from winning." << endl;
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


/* *********************************************************************
Function Name:setFirstPlayer
Purpose: set which player goes first
Parameters: none
Return Value: none
Local Variables: none
Algorithm: roll two dice to see which player goes first for each player, keep rolling
			until the tosses are not equal to each other
Assistance Received: none
********************************************************************* */
void Game::setFirstPlayer()
{
	while (m_playerDiceSum == m_computerDiceSum) {
		if (!m_diceFile) {
			m_playerDiceSum = rollDice(*m_human);
			m_computerDiceSum = rollDice(*m_computer);
		}
		else if (m_diceFile) {
			if (m_human->m_diceRolls.empty()) {
				m_diceFile = false;
			}
			else {
				m_playerDiceSum = m_human->m_diceRolls.front();
				cout << "Dice sum: " << m_playerDiceSum << endl;
				m_human->m_diceRolls.pop();
				m_computerDiceSum = m_human->m_diceRolls.front();
				cout << "Dice sum: " << m_computerDiceSum << endl;
				m_human->m_diceRolls.pop();
			}
		}
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

/* *********************************************************************
Function Name: saveGame
Purpose: to serialize a game's state
Parameters:	none
Return Value: true if successfully created a save file, false if not
Local Variables: string input - file line buffer
				 ifstream myFile - file to be saved to
Algorithm: go line by line
			write playeer labels,
			write squares controlled for each player
			write stats for each player
			write who the first player was
			write who the next turn is
Assistance Received: none
********************************************************************* */
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

		// save turns
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

/* *********************************************************************
Function Name: isGameStarted
Purpose: check if game has started yet
Parameters: none
Return Value: true if game started, else returns false
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Game::isGameStarted() const {
	return m_gameStarted;
}

/* *********************************************************************
Function Name: isLoaded
Purpose: check if a loaded game
Parameters: none
Return Value: true if is a loaded game, false if new game
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Game::isLoaded() const
{
	return m_isLoaded;
}

/* *********************************************************************
Function Name: setIsLoaded
Purpose: set if its a loaded game
Parameters: bool a_flag - true if loaded, false if not
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void Game::setIsLoaded(bool a_flag)
{
	m_isLoaded = a_flag;
}

/* *********************************************************************
Function Name: rollDice
Purpose: function to roll two dice
Parameters: Player& a_player - reference to the player rollling the dice
Return Value: int - sum of dice roll
Local Variables: int value1 - sum of first die roll
				 int value2 - sum of second die roll
				 int value - sum of both dice rolled
Algorithm: 1) get current time and use that as a seed number for a the random number
			  generation
		   2) do it twice for two dice
		   3) return sum of both dice
Assistance Received: none
********************************************************************* */
int Game::rollDice(Player& a_player)
{
	Sleep(2000);
	srand(static_cast<unsigned int>(time(0)));
	int value = 0;
	int value1 = rand() % 6 + 1;
	int value2 = rand() % 6 + 1;
	value = value1 + value2;
	cout << a_player.getPlayerType() << " rolled a " << value1 << " and a " << value2 << ". A total of " << value << "." << endl;
	return value;
}

/* *********************************************************************
Function Name: rollDie
Purpose: function to roll a die
Parameters:  Player& a_player - reference to the player rollling the die
Return Value: int - die roll
Local Variables: int value - random value generated between 1 -6 
Algorithm: 1) get current time and use that as a seed number for the random
			  number generation
	       2) roll dice and return value
Assistance Received: none
********************************************************************* */
int Game::rollDie(Player& a_player)
{
	Sleep(2000);
	srand(static_cast<unsigned int>(time(0)));
	int value;
	value = rand() % 6 + 1;
	cout << a_player.getPlayerType() << " rolled a " << value << "." << endl;
	return value;
}


/* *********************************************************************
Function Name: getInputFromUser
Purpose: get input from user
Parameters: Human &user - 
			string a_inputType - 
Return Value: return string inputted by user after validating
Local Variables: bool validInput - is it valid string flag
				 string userChoice - user's selection
Algorithm: 1) get user's selection as string
		   2) check validation functions in Human class with the corresponding 
			  input type
		   3) true if valid input, return false if invalid input and ask
			  user to input again
	       4) return string input
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: playGame
Purpose: starting point of a round
Parameters: a_roundNumber - round number: used in tournmen
Return Value: return flase if game was issued a request to quit
Local Variables: string input - variable to hold user's input
Algorithm: 1) check if its a new game or loaded game
		   2) if loaded game flag is ture, load state of game from a file
		   3) else its  anew game, set a new round, and set who goes first
		   4) then finally check if a player hass won
Assistance Received: none
********************************************************************* */
bool Game::playGame(int a_roundNumber) {
	// begin game round
	string input;
	cout << "Begin round #" << a_roundNumber << " !\n" << endl;
	// check if loaded game
	if (!isLoaded()) {
		askGameRule();
		input = getInputFromUser(*m_human, "gamerule");
		setGameRule(input);

		//myGame.setGameRule(temp);

		setNewRound();
	}
	m_boardView = BoardView(*m_human, *m_computer, m_board);
	m_gameStarted = true;

	// if not loaded game, set first player
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

	// keep playing turns until someone wins
	while (!isWon()) {
		if (isFirstPlay()) {
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
			m_boardView.displayTurns();
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
			m_boardView.displayTurns();
		}

		// if someone wins, calculate score and announce winner
		if (isWon()) {
			if (getWinner()->getPlayerType() == "Human") {
				//sum of all uncovered squares of computer
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
				//sum of all uncovered squares of computer
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
