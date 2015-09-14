#include "Human.h"
#include <iostream>
#include <string>



Human::Human()
{
}

Human::Human(int a_gameRule)  : Player(a_gameRule)
{
	Player::setPlayerType("Human");

}

Human::~Human()
{
}


bool Human::verifyInput(string a_input, string a_inputType) {
	/*
	if (a_inputType == "roll") {
		return verifyRollDice(a_input);
	}
	else if (a_inputType == "rollChoice") {
		return verifyRollChoice(a_input);
	}
	else if (a_inputType == "cover") {
		return verifyCoverSquare(a_input);
	}
	else if (a_inputType == "uncover") {
		return verifyUncoverSquare(a_input);
	}
	else if (a_inputType == "save" || a_input == "load") {
		return verifyFileName(a_input);
	}
	else {
		return false;
	}
	*/
	return true;
}
/*
bool Human::verifyGameRule(string a_selection)
{
	int gameRule;
	try {
		gameRule = stoi(a_selection);
	}
	catch (invalid_argument& e) {
		cerr << e.what() << endl;
		return false;
	}

	if (gameRule < 9 || gameRule > 12) return false;
	return true;
}
*/