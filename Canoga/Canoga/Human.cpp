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
	else if (a_inputType == "one") {
		return verifyOneRoll(a_input);
	}
	else if (a_inputType == "two") {
		return verifyTwoRoll(a_input);
	}
	else if (a_inputType == "rollchoice") {
		return verifyRollChoice(a_input);
	}
	else if (a_inputType == "cover") {
		return verifyCoverSquare(a_input);
	}
	else if (a_inputType == "uncover") {
		return verifyUncoverSquare(a_input);
	}
	else if (a_inputType == "coveruncover") {
		return verifyCoverUncoverSquare(a_input);
	}
	else if (a_inputType == "number") {
		return verifyNumber(a_input);
	}
	else if (a_inputType == "save" || a_input == "load") {
		return verifyFileName(a_input);
	}
	else if (a_inputType == "side") {
		return verifySideSelection(a_input);
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
	if (selection == "roll") return true;
	else return false;
}
bool Human::verifyOneRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one") return true;
	else return false;
}
bool Human::verifyTwoRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "two") return true;
	else return false;
}
bool Human::verifyRollChoice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one" || selection == "two") return true;
	else return false;
}
bool Human::verifyCoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover") return true;
	return false;
}
bool Human::verifyUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "uncover") return true;
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
bool Human::verifySideSelection(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "uncover")
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
	if (is_number(a_selection) && stoi(a_selection) <= m_gameRule && stoi(a_selection) >= 1 )
	{
			return true;
	}
	else if (a_selection == "-1") {
		return true;
	}
	else 
	{
		return false;
	}
}

bool Human::verifyCoverUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "uncover")
	{
		return true;
	}
	else {
		return false;
	}
}

string Human::toLowerCase(string a_selection) {
	string lower_str = a_selection;
	transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
	return lower_str;


}

void Human::setGameRule(int a_gameRule)
{
	m_gameRule = a_gameRule;
}

bool Human::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
