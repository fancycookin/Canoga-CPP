#include "Game.h"
#include "Player.h"
#include "BoardView.h"
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
	Player ihab, computer;
	ihab = Player(temp);
	computer = Player(temp);

	BoardView bview = BoardView(ihab);
	bview.RefreshDisplay();
	bview.Display();
	ihab.setCoverSquare(5);
	bview.RefreshDisplay();
	bview.Display();
	cout << "Ihab's score:" << endl;
	cout << ihab.getScore() << endl;
	cout << "CPU's score:" << endl;
	cout << computer.getScore() << endl;

	map<string, bool> hi = map<string, bool>();
	hi.insert(pair<string,bool>("hi", false));
	hi["hi"] = true;
	cout << hi["hi"];

	return 0;
}