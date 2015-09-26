#include "BoardView.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>

BoardView::BoardView() 
{

}
BoardView::BoardView(Player &a_player, Player &a_player2, Board &a_board)
{
	m_board = &a_board;
	m_player = &a_player;
	m_player2 = &a_player2;
}


BoardView::~BoardView()
{
}

void BoardView::refreshDisplay()
{
	if (system("CLS")) system("clear");
}

void BoardView::display()
{
	// Open board borders
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";

	
	cout << "CPU";
	cout.width(4);
	cout.fill(' ');
	cout << ":\t";

	// CPU HUD
	auto it2 = m_board->getComputerRows()->begin();
	//auto it2 = m_player2->getBoard()->getMap()->begin();
	for (it2; it2 != m_board->getComputerRows()->end();++it2) {
		if (it2->second) cout << "|*" << it2->first << "*";
		else cout << "| " << (it2->first) << " ";
	}
	cout << "|\n";
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";


	cout << "1P";
	cout.width(5);
	cout.fill(' ');
	cout << ":\t";

	// Player HUD
	auto it = m_board->getHumanRows()->begin();
	//auto it = m_player->getBoard()->getMap()->begin();
	for (it; it != m_board->getHumanRows()->end();++it) {
		if (it->second) cout << "|*" << it->first << "*";
		else cout << "| " << (it->first) << " ";
	}

	
	
	// Close board borders
	cout << "|\n";
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";
}


void BoardView::displayScore()
{
	cout << "    1P";
	for (int i = 0; i < 36; i++) {
		cout << " ";
	}
	cout << "CPU\n";
	cout << "Tournment Score : " << m_player->getScore();
	for (int i = 0; i < 20; i++) {
		cout << " ";
	}
	cout << "Tournment Score : " << m_player2->getScore() << endl;
	cout << "Round Score: " << m_player->getRoundScore();
	for (int i = 0; i < 25; i++) {
		cout << " ";
	}
	cout << "Round Score: " << m_player2->getRoundScore() << endl;
	cout << "Wins  : " << m_player2->getWins();
	for (int i = 0; i < 30; i++) {
		cout << " ";
	}
	cout << "Wins  : " << m_player->getWins() << endl;
}

void BoardView::displayTurns() {
	string firstPlayer;
	string turnPlayer;
	if (m_player->getWentFirst()) {
		firstPlayer = m_player->getPlayerType();
	}
	else {
		firstPlayer = m_player2->getPlayerType();
	}

	if (m_player->isTurn()) {
		turnPlayer = m_player->getPlayerType();
	}
	else {
		turnPlayer = m_player2->getPlayerType();
	}
	cout << "Current Turn : " << turnPlayer << endl;
	cout << "First Player : " << firstPlayer << endl;
}
