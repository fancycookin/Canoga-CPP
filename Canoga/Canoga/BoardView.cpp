#include "BoardView.h"
#include "Board.h"
#include "Player.h"
#include <iostream>
#include <string>


BoardView::BoardView(Player &a_player)
{
	m_player = &a_player;
}


BoardView::~BoardView()
{
}

void BoardView::RefreshDisplay()
{
	if (system("CLS")) system("clear");
}

void BoardView::Display()
{

	int test = m_player->getBoard().getMaxRows();
	//map<int, bool> *playerRows;
	//playerRows = m_player.getBoard().getMap();
	for (int i = 0; i < m_player->getBoard().getMaxRows() * 2; i++) {
		cout << "--";
	}
	cout << "\n";
	
	//auto it= m_player->getBoard().getMap()->begin();

	//it->first;
	/*
	for (it = playerRows->begin(); it != playerRows->end();++it) {
		if (it->second) cout << "|*" << it->first << "*|";
		else cout << "|" << (it->first) << "|";
	}
	*/
	//it = m_player->getBoard().getMap()->begin();
	//it->first;
	//it = m_player->getBoard().getMap()->end();
	/*
	for (it = m_player->getBoard().getMap()->begin(); it != m_player->getBoard().getMap()->end();++it) {
		if (it->second) cout << "|*" << it->first << "*|";
		else cout << "|" << (it->first) << "|";
	}
	*/
	cout << "\n";
}

