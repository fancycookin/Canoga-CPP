#include <iostream>
#include "Player.h"
#include "Tournment.h"
using namespace std;

int main() {
	Human P1 = Human();
	Computer CPU = Computer();
	Tournment tourny = Tournment();
	tourny.startGame();
	return 0;
}