#include "Human.h"
#include <iostream>
#include <string>

Human::Human()  : Player()
{
	Player::setPlayerType("Human");

}

Human::~Human()
{
}


bool Human::verifyInput(string a_input, string a_inputType) {
	
	if (a_inputType == "start") {
		return verifyStartGame(a_input);
	}
	else if (a_inputType == "roll") {
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
	else if (a_inputType == "number") {
		return verifyNumber(a_input);
	}
	else if (a_inputType == "save" || a_input == "load") {
		return verifyFileName(a_input);
	}
	else {
		return false;
	}
	
	return true;
}
bool Human::verifyGameRule(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyRollDice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyRollChoice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyCoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyFileName(string a_selection)
{
	string selection = toLowerCase(a_selection);
	return false;
}
bool Human::verifyStartGame(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "play" || selection == "quit")
	{
		return true;
	}
	else {
		return false;
	}
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

bool Human::verifyNumber(string a_selection)
{
	if (is_number(a_selection))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string Human::toLowerCase(string a_selection) {
	string lower_str = a_selection;
	transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
	return lower_str;


}

bool Human::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
