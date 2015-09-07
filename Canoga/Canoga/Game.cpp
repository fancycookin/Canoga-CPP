#include "Game.h"
#include "Player.h"
#include "BoardView.h"
#include "Human.h"
#include "Computer.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

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

	BoardView playerBoardView = BoardView(player, CPU);
	//BoardView CPUBoardView = BoardView(CPU);
	playerBoardView.refreshDisplay();
	playerBoardView.display();
	//CPUBoardView.Display();
	player.setCoverSquare(5);
	playerBoardView.refreshDisplay();
	playerBoardView.display();
	
	playerBoardView.displayScore();

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