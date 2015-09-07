#include "Game.h"
#include "Player.h"
#include "BoardView.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <string>

using namespace std;


Game::Game()
{
}


Game::~Game()
{
}

int Game::GetGameRule()
{
	return m_gameRule;
}

bool Game::SetGameRule(int a_gameRule)
{
	m_gameRule = a_gameRule;
	return true;
}

int main() {
	int temp;
	cout << "Enter number of rows that you'd like:";
	cin >> temp;

	Human player = Human(temp);
	Computer CPU = Computer(temp);

	BoardView playerBoardView = BoardView(player);
	BoardView CPUBoardView = BoardView(CPU);
	playerBoardView.RefreshDisplay();
	playerBoardView.Display();
	CPUBoardView.Display();
	player.setCoverSquare(5);
	playerBoardView.RefreshDisplay();
	playerBoardView.Display();
	CPUBoardView.Display();
	cout << "Player's score:" << endl;
	cout << player.getScore() << endl;
	cout << "CPU's score:" << endl;
	cout << CPU.getScore() << endl;

	/*
	map<string, bool> hi = map<string, bool>();
	hi.insert(pair<string,bool>("hi", false));
	hi["hi"] = true;
	cout << hi["hi"];
	*/

	return 0;
}