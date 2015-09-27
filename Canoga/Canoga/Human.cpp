/************************************************************
/* Name: Ihab Hamid                                         *
/* Project : Canoga - C++ - OPL 2015                        *
/* Class : CMPS 366 - Organization of Programming Languages *
/* Date : 9/25/2015                                         *
/************************************************************/
#include "Human.h"
#include <iostream>
#include <string>
#include <regex>

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
Human::Human()  : Player()
{
	Player::setPlayerType("Human");
	m_gameRule = 0;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
Human::~Human()
{
}


/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyInput(string a_input, string a_inputType) {

	if (a_inputType == "start") {
		return verifyStartGame(a_input);
	}
	else if (a_inputType == "help") {
		return verifyHelp(a_input);
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
	else if (a_inputType == "gamerule") {
		return verifyGameRule(a_input);
	}
	else if (a_inputType == "filename") {
		return verifyFileName(a_input);
	}
	else if (a_inputType == "save") {
		return verifySaveGame(a_input);
	}
	else {
		return false;
	}
	
	return true;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyGameRule(string a_selection)
{
	if ((is_number(a_selection) && stoi(a_selection) == 9) || (is_number(a_selection) && stoi(a_selection) == 10) || (is_number(a_selection) && stoi(a_selection) == 11)) {
		return true;
	}
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyHelp(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "help") return true;
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyRollDice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "roll") return true;
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyOneRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one") return true;
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyTwoRoll(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "two") return true;
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyRollChoice(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "one" || selection == "two") return true;
	else return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyCoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "help") return true;
	return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "uncover" || selection == "help") return true;
	return false;
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyFileName(string a_selection)
{
	bool found = false;
	string selection = toLowerCase(a_selection);
	regex findChars("(\\\\|/|:|\\*|\\?|\"|<|>|\\|)");
	regex_iterator<string::iterator> myIterator(selection.begin(), selection.end(), findChars);
	regex_iterator<string::iterator> endIterator;
	while (myIterator != endIterator) {
		found = true;
		myIterator++;
	}
	if (int(selection.length()) < 30 && found == false) {
		return true;
	}
	if (selection == "back") {
		return true;
	}
	else {
		return false;
	}
}
/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyStartGame(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "play" || selection == "load" || selection == "quit")
	{
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyNumber(string a_selection)
{
	if (is_number(a_selection) && stoi(a_selection) <= m_gameRule && stoi(a_selection) >= 1)
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifyCoverUncoverSquare(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "cover" || selection == "uncover" || selection == "help")
	{
		return true;
	}
	else {
		return false;
	}
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::verifySaveGame(string a_selection)
{
	string selection = toLowerCase(a_selection);
	if (selection == "yes" || selection == "no") return true;
	return false;
}


/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
string Human::toLowerCase(string a_selection) {
	string lower_str = a_selection;
	transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
	return lower_str;


}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
void Human::setGameRule(int a_gameRule)
{
	m_gameRule = a_gameRule;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Human::is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}
